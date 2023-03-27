#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>
#include "Client.h"
#include "Server.h"

#define CLIENT 0
#define SERVER 1
#define currentProgram CLIENT

//Having the preprocessor directive means that I can have identical code run but function as the client or server
//depending on the value of the directive. This would be incredibly useful and save having duplicate code if I figured
//out how to have one solution configured to run the same code twice with a different value in the directive. However,
//since there was no time for it, the actual purpose of the directive is impractical as it currently stands, and doesn't
//prevent any duplicate code from being made since there is still another copy of the same project.

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