#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>
#include "Client.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
	Comms* comms = new Comms;
	Client* client = new Client;
	comms->ServiceSetup();
	client->WsaerrCheck();
	client->ClientSocketSetup();
	client->ClientServiceSetup();
	client->SendAndReceiveFromServer();

	system("pause");
	WSACleanup();
	return 0;

}
