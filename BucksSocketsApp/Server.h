#pragma once
#include "Comms.h"
class Server : public Comms
{
public:
	DWORD WINAPI ServerThread(LPVOID lpParam);
	SOCKADDR_STORAGE from;
	int retval, fromlen, socket_type;
	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];
	SOCKET serverSocket, acceptSocket;

	int WsaerrCheck();
	int ServerSocketSetup();
	int ServerServiceSetup();
	void ReceiveAndSendToClient();
};

