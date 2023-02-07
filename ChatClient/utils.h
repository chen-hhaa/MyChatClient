#pragma once
#include <stdio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<Windows.h>

#include<string>
#include<iostream>
using namespace std;

void welcomeInfo(SOCKET sock);

string logIn(SOCKET sock);
string registerC(SOCKET sock);