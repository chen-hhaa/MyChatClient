#define _CRT_SECURE_NO_WARNINGS

#include<WinSock2.h>
#include<WS2tcpip.h>
#include<Windows.h>
#include<stdio.h>
#include<string>

#include "utils.h"
#include "ConfigReader.h"

#pragma comment(lib,"Ws2_32.lib")
#define BUF_SIZE 1024

char szMsg[BUF_SIZE];
std::string client_name = "";


unsigned SendMsg(void* arg)
{
	SOCKET sock = *((SOCKET*)arg);
	while (1)
	{

		//scanf("%s", szMsg);
		cin.getline(szMsg, 1024);
		/*
		if (client_name == "") {
			client_name = szMsg;
		}*/
		if (!strcmp(szMsg, "QUIT") || !strcmp(szMsg, "quit"))
		{
			//�����˳���Ϣ
			//std::string quit_msg = client_name + " quit the chat room!";
			//send(sock, quit_msg.c_str(), quit_msg.size(), 0);
			closesocket(sock);
			exit(0);
		}
		string flagMsg = szMsg;
		flagMsg = "[3]" + flagMsg;
		//cout << flagMsg << endl;
		send(sock, flagMsg.c_str(), flagMsg.size(), 0);
	}
	return 0;
}
unsigned RecvMsg(void* arg)
{
	SOCKET sock = *((SOCKET*)arg);

	char msg[BUF_SIZE];
	while (1)
	{
		int len = recv(sock, msg, sizeof(msg) - 1, 0);
		if (len == -1)
		{
			return -1;
		}
		msg[len] = '\0';
		printf("%s\n", msg);
	}
	return 0;
}


int main()
{
	//��ʼ��socket����
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return -1;
	}

	//����socket
	SOCKET hSock;
	hSock = socket(AF_INET, SOCK_STREAM, 0);

	//��ȡ�����ļ�
	ConfigReader cfg_reader("connect.conf");
	cfg_reader.readConfig();
	unordered_map<string, string> cfg_dic = cfg_reader.get_config_dic();
	//�󶨶˿�
	SOCKADDR_IN servAdr;
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_port = htons(atoi(cfg_dic["server_port"].c_str()));
	inet_pton(AF_INET, cfg_dic["server_host_ip"].c_str(), &servAdr.sin_addr); // inet_pton������IP��ַ�ӵ��ʮ����ת��4�ֽ�������


	//���ӷ�����
	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		printf("connect error : %d", GetLastError());
		return -1;
	}
	else
	{
		// ��ӭ����, ���û�ѡ���¼����ע��ѡ��
		welcomeInfo(hSock);
	}

	//ѭ������Ϣ
	HANDLE hSendHand = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SendMsg, (void*)&hSock, 0, NULL);

	//ѭ������Ϣ
	HANDLE hRecvHand = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvMsg, (void*)&hSock, 0, NULL);


	//�ȴ��߳̽���
	WaitForSingleObject(hSendHand, INFINITE);
	WaitForSingleObject(hRecvHand, INFINITE);


	closesocket(hSock);
	WSACleanup();

	return 0;
}