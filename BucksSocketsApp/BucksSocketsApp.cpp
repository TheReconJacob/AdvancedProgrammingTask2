#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>
#include "Client.h"
#include "Server.h"

#define CLIENT 0
#define SERVER 1
#define currentProgram SERVER

int _tmain() {
	#ifdef currentProgram
	Comms* comms = new Comms;
	comms->ServiceSetup();
	if (currentProgram == CLIENT)
	{
		//Client Side
		Client* client = new Client;

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
	}
	else
	{
		//Server Side
		Server* server = new Server;

		try {
			server->WsaerrCheck();
			server->ServerSocketSetup();
			server->ServiceSetup();
			server->ReceiveAndSendToClient();
		}
		catch (const char* exception) {
			std::cout << exception << std::endl;
			WSACleanup();
			return 0;
		}
	}
	system("pause");
	WSACleanup();
	return 0;
	#endif
}