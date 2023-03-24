#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>
#include "Server.h"

#define TRUE 1
#define FALSE 0
#define enableServer TRUE


int main() {
	#ifdef enableServer
	if (enableServer == FALSE)
	{
		std::cout << "Server has been disabled!" << std::endl;
		return 0;
	}
	#endif
	Comms* comms = new Comms;
	Server* server = new Server;
	comms->ServiceSetup();

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

	system("pause");
	WSACleanup();
	return 0;
}