#include "winsock2.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
BOOL RecvLine(SOCKET s, char* buf); //读取一行数据

int main(int argc, char* argv[])
{
	const int BUF_SIZE = 64;

	WSADATA wsd; //WSADATA变量
	SOCKET sHost; //服务器套接字
	SOCKADDR_IN servAddr; //服务器地址
	char buf[BUF_SIZE]; //接收数据缓冲区
	char bufRecv[BUF_SIZE];
	int retVal; //返回值
	//初始化套结字动态库
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed!" << endl;
		return -1;
	}
	//创建套接字
	sHost = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == sHost)
	{
		cout << "socket failed!" << endl;
		WSACleanup();//释放套接字资源
		return  -1;
	}

	//设置服务器地址
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = 16777343;
	servAddr.sin_port = htons((short)3999);
	int nServAddlen = sizeof(servAddr);

	sockaddr fromAddr;
	int addrLen = sizeof(fromAddr);
	while (true)
	{
		//向服务器发送数据
		ZeroMemory(buf, BUF_SIZE);
		cout << " 向服务器发送数据:  ";
		cin >> buf;
		retVal = sendto(sHost, buf, strlen(buf), 0, (struct sockaddr*)&servAddr,sizeof(servAddr));
		if (SOCKET_ERROR == retVal)
		{
			cout << "send failed!" << endl;
			closesocket(sHost); //关闭套接字
			WSACleanup(); //释放套接字资源
			return -1;
		}
		//RecvLine(sHost, bufRecv);
		ZeroMemory(bufRecv, BUF_SIZE);
		recvfrom(sHost, bufRecv, BUF_SIZE, 0, &fromAddr, &addrLen); // 接收服务器端的数据， 只接收5个字符
		cout << endl << "从服务器接收数据：" << bufRecv;
		cout << "\n";
	}
	//退出
	closesocket(sHost); //关闭套接字
	WSACleanup(); //释放套接字资源
	return 0;
}
