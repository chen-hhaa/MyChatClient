
#include "utils.h"

void welcomeInfo(SOCKET sock)
{
	printf("---------------��ӭ����˽�������ң����ȵ�¼(1)��ע���˺�(2)---------------\n");
	printf("�����룺");
	int flag = 2;
	scanf("%d", flag);
	if (flag == 1) {
		logIn(sock);
		cout << "��¼�ɹ���" << endl;
	}
	else if(flag == 2){
		registerC();
	}
}

void logIn(SOCKET sock)
{
	string user_name, pwd;
	cout << "�û�����" << endl;
	getline(cin, user_name);

	cout << "���룺" << endl;
	getline(cin, pwd);

	string msg = "LOGIN:" + user_name + pwd;
	send(sock, msg.c_str(), msg.size(), 0);


}
