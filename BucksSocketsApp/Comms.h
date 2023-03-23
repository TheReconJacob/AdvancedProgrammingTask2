#pragma once
#include <WinSock2.h>
class Comms
{
private:
	WORD wVersionRequested = MAKEWORD(2, 2);

protected:
	int byteCount = SOCKET_ERROR;
	char sendBuffer[200];
	char receiveBuffer[200] = "";
	int port = 55555;
	WSADATA wsaData;
	int wsaerr = WSAStartup(wVersionRequested, &wsaData);
	sockaddr_in service;

public:
	virtual void ServiceSetup();
};