
#include "utils.h"

void welcomeInfo(SOCKET sock)
{
	printf("---------------��ӭ����˽�������ң����ȵ�¼(1)��ע���˺�(2)---------------\n");
	printf("�����룺");
	int flag = 2;
	scanf("%d", flag);
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
	getline(cin, user_name);

	cout << "���룺" << endl;
	getline(cin, pwd);

	string msg = "[login]:[user_name]" + user_name + "[password]" + pwd;
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
