
#include "utils.h"

void welcomeInfo(SOCKET sock)
{
	printf("---------------��ӭ����˽�������ң����ȵ�¼(1)��ע���˺�(2)---------------\n");
	printf("�����룺");
	int flag = 2;
	cin >> flag;
	if (flag == 1) {
		while (logIn(sock) != "ok") {
			cout << "��¼ʧ�ܣ������ԡ�" << endl;
		}
		cout << "��¼�ɹ���" << endl;
	}
	else if(flag == 2){
		//TODO: registerC();
	}
}

string logIn(SOCKET sock)
{
	string user_name, pwd;
	cout << "�û�����" << endl;
	cin >> user_name;
	//getline(cin, user_name);

	cout << "���룺" << endl;
	cin >> pwd;
	//getline(cin, pwd);

	// string msg = "[login]:[user_name]" + user_name + "[password]" + pwd;
	string msg = "[1][" + user_name + "][" + pwd + ']'; //����˸��ݸ�ʽ���н��� ��һ��[]������1��ʾ��¼��Ϣ
	send(sock, msg.c_str(), msg.size(), 0);

	char recv_msg[1024];
	int len = recv(sock, recv_msg, sizeof(msg) - 1, 0);
	if (len == -1)
	{
	}
	recv_msg[len] = '\0';
	string result = recv_msg;
	return result;
	
}
