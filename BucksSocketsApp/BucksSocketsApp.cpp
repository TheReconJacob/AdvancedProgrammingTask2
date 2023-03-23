#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>
#include "Server.h"

int main(int argc, char* argv[]) {
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