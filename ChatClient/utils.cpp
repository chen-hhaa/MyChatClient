
#include "utils.h"

void GBKTOUTF8(string& strGBK)//ת�� GBK����ת��UTF8���룬����windows��������Ч
{
	int len = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	wchar_t* wszUtf8 = new wchar_t[len];
	memset(wszUtf8, 0, len);
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, wszUtf8, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char* szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);
	strGBK = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
}

void welcomeInfo(SOCKET sock)
{
	printf("---------------��ӭ����˽�������ң����ȵ�¼(1)��ע���˺�(2)---------------\n");
	printf("�����룺");
	int flag = 2;
	cin >> flag;
	string response;
	if (flag == 1) {
		while ((response = logIn(sock)) != "ok") {
			cout << response << " �����ԡ�" << endl;
		}
		cout << "��¼�ɹ������Կ�ʼ������" << endl;
	}
	else if (flag == 2) {
		//TODO: registerC();
		while ((response = registerC(sock)) != "ok") {
			cout << response << " �����ԡ�" << endl;
		}
		cout << "�˺�ע��ɹ������Կ�ʼ������" << endl;
	}
}



string logIn(SOCKET sock)
{
	string user_name, pwd;
	cout << "-�û�����" << endl;
	cin >> user_name;
	//getline(cin, user_name);

	cout << "-���룺" << endl;
	cin >> pwd;
	//getline(cin, pwd);

	// string msg = "[login]:[user_name]" + user_name + "[password]" + pwd;
	string msg = "[1][" + user_name + "][" + pwd + ']'; //����˸��ݸ�ʽ���н��� ��һ��[]������1��ʾ��¼��Ϣ
	send(sock, msg.c_str(), msg.size(), 0);

	char recv_msg[1024];
	int len = recv(sock, recv_msg, sizeof(msg) - 1, 0);
	if (len == -1)
	{
		return "";
	}
	recv_msg[len] = '\0';
	string result = recv_msg;
	return result;
}

string registerC(SOCKET sock) {
	string user_name, pwd;
	cout << "-�û�����" << endl;
	cin >> user_name;
	//getline(cin, user_name);

	cout << "-���룺" << endl;
	cin >> pwd;

	string msg = "[2][" + user_name + "][" + pwd + ']'; // [2]������ע����Ϣ
	send(sock, msg.c_str(), msg.size(), 0);

	char recv_msg[1024];
	int len = recv(sock, recv_msg, sizeof(msg) - 1, 0);
	if (len == -1)
	{
		return "";
	}
	recv_msg[len] = '\0';
	string result = recv_msg;
	return result;
}
