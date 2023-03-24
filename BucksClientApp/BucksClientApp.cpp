#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>
#include "Client.h"

#define TRUE 1
#define FALSE 0
#define enableClient TRUE

int _tmain() {
	#ifdef enableClient
	if (enableClient == FALSE)
	{
		std::cout << "Client has been disabled!" << std::endl;
		return 0;
	}
	#endif
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