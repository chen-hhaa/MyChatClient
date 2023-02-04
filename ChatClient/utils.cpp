
#include "utils.h"

void welcomeInfo(SOCKET sock)
{
	printf("---------------欢迎来到私人聊天室，请先登录(1)或注册账号(2)---------------\n");
	printf("请输入：");
	int flag = 2;
	scanf("%d", flag);
	if (flag == 1) {
		while (logIn(sock) != "ok") {
			cout << "登录失败，请重试。" << endl;
		}
		cout << "登录成功！" << endl;
	}
	else if(flag == 2){
		//TODO: registerC();
	}
}

string logIn(SOCKET sock)
{
	string user_name, pwd;
	cout << "用户名：" << endl;
	getline(cin, user_name);

	cout << "密码：" << endl;
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
