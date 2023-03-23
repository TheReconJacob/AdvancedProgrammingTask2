#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>
#include "Server.h"

int main(int argc, char* argv[]) {
	Comms* comms = new Comms;
	Server* server = new Server;
	comms->ServiceSetup();
	server->WsaerrCheck();
	server->ServerSocketSetup();
	server->ServerServiceSetup();
	server->ReceiveAndSendToClient();

	system("pause");
	WSACleanup();
	return 0;
}