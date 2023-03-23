#pragma once
#include <WinSock2.h>
class Comms
{
public:
	int port = 55555;
	int byteCount = SOCKET_ERROR;
	char sendBuffer[200];
	char receiveBuffer[200] = "";
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	int wsaerr = WSAStartup(wVersionRequested, &wsaData);
	sockaddr_in service;

	virtual void ServiceSetup();
};

