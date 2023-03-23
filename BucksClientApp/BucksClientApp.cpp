#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>
#include "Client.h"

int _tmain(int argc, _TCHAR* argv[]) {
	Comms* comms = new Comms;
	Client* client = new Client;
	comms->ServiceSetup();

	try {
		client->WsaerrCheck();
		client->ClientSocketSetup();
		client->ServiceSetup();
		client->SendAndReceiveFromServer();
	}
	catch (const char* exception) {
		std::cout << exception << std::endl;
		WSACleanup();
		return 0;
	}

	system("pause");
	WSACleanup();
	return 0;
}
