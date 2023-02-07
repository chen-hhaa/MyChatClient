
#include "utils.h"

void GBKTOUTF8(string& strGBK)//转码 GBK编码转成UTF8编码，仅在windows环境下有效
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
	printf("---------------欢迎来到私人聊天室，请先登录(1)或注册账号(2)---------------\n");
	printf("请输入：");
	int flag = 2;
	cin >> flag;
	string response;
	if (flag == 1) {
		while ((response = logIn(sock)) != "ok") {
			cout << response << " 请重试。" << endl;
		}
		cout << "登录成功！可以开始聊天了" << endl;
	}
	else if (flag == 2) {
		//TODO: registerC();
		while ((response = registerC(sock)) != "ok") {
			cout << response << " 请重试。" << endl;
		}
		cout << "账号注册成功！可以开始聊天了" << endl;
	}
}



string logIn(SOCKET sock)
{
	string user_name, pwd;
	cout << "-用户名：" << endl;
	cin >> user_name;
	//getline(cin, user_name);

	cout << "-密码：" << endl;
	cin >> pwd;
	//getline(cin, pwd);

	// string msg = "[login]:[user_name]" + user_name + "[password]" + pwd;
	string msg = "[1][" + user_name + "][" + pwd + ']'; //服务端根据格式进行解析 第一个[]的数字1表示登录信息
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
	cout << "-用户名：" << endl;
	cin >> user_name;
	//getline(cin, user_name);

	cout << "-密码：" << endl;
	cin >> pwd;

	string msg = "[2][" + user_name + "][" + pwd + ']'; // [2]代表是注册信息
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
