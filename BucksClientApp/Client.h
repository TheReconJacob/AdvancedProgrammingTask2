#pragma once
#include "Comms.h"
class Client : public Comms
{
public:
	SOCKET clientSocket = INVALID_SOCKET;

	int WsaerrCheck();

	int ClientSocketSetup();

	int ClientServiceSetup();

	void SendAndReceiveFromServer();
};

