#pragma once
#include "Comms.h"
class Client : public Comms
{
public:
	SOCKET clientSocket = INVALID_SOCKET;

	void WsaerrCheck();

	void ClientSocketSetup();

	void ServiceSetup();

	void SendAndReceiveFromServer();
};

