#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>
#include "Client.h"

int _tmain(int argc, _TCHAR* argv[]) {
	Comms* comms = new Comms;
	Client* client = new Client;
	comms->ServiceSetup();
	client->WsaerrCheck();
	client->ClientSocketSetup();
	client->ServiceSetup();
	client->SendAndReceiveFromServer();

	system("pause");
	WSACleanup();
	return 0;

}
