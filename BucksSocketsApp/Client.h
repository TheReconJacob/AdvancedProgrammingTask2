#pragma once
#include "Comms.h"
class Client : public Comms
{
private:
	SOCKET clientSocket = INVALID_SOCKET;

public:
	void WsaerrCheck();
	void ClientSocketSetup();
	void ServiceSetup();
	void SendAndReceiveFromServer();
};

