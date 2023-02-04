
#include "utils.h"

void welcomeInfo(SOCKET sock)
{
	printf("---------------欢迎来到私人聊天室，请先登录(1)或注册账号(2)---------------\n");
	printf("请输入：");
	int flag = 2;
	scanf("%d", flag);
	if (flag == 1) {
		logIn(sock);
		cout << "登录成功！" << endl;
	}
	else if(flag == 2){
		registerC();
	}
}

void logIn(SOCKET sock)
{
	string user_name, pwd;
	cout << "用户名：" << endl;
	getline(cin, user_name);

	cout << "密码：" << endl;
	getline(cin, pwd);

	string msg = "LOGIN:" + user_name + pwd;
	send(sock, msg.c_str(), msg.size(), 0);


}
