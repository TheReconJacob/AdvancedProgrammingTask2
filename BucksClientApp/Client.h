#pragma once
#include "Comms.h"
class Client : public Comms
{
public:
	SOCKET clientSocket = INVALID_SOCKET;
	sockaddr_in clientService;

	int WsaerrCheck();

	int ClientSocketSetup();

	int ClientServiceSetup();

	void SendAndReceiveFromServer();
};

