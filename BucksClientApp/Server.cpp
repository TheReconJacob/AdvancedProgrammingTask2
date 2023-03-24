#include "Server.h"
#include <iostream>
#include <tchar.h>
#include <WS2tcpip.h>

void Server::WsaerrCheck()
{
	if (wsaerr != 0) {
		throw("The Winsock dll not found!");
	}
	else {
		std::cout << "The Winsock dll found!" << std::endl;
		std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
	}
}

void Server::ServerSocketSetup()
{
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		throw("Error at socket(): " + WSAGetLastError());
	}
	else {
		std::cout << "socket() is OK!" << std::endl;
	}
}

void Server::ServiceSetup()
{
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		closesocket(serverSocket);
		throw("bind() failed: " + WSAGetLastError());
	}
	else {
		std::cout << "bind() is OK!" << std::endl;
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR)
		throw("listen(): Error listening on socket " + WSAGetLastError());
	else
		std::cout << "listen() is OK, I'm waiting for connections..." << std::endl;
}

void Server::ReceiveAndSendToClient()
{
	acceptSocket = accept(serverSocket, NULL, NULL);
	int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	char buffer[200] = "";
	while (1) {
		bytesRecv = recv(acceptSocket, buffer, 200, 0);
		if (bytesRecv == SOCKET_ERROR)
			throw("Server: recv() error " + WSAGetLastError());
		else {
			//cout << "Server: recv() is OK." << endl;
			std::cout << "From Client: " << buffer << std::endl;
			//cout << "Server: Bytes received: " << bytesRecv << endl;
		}

		if (strcmp(buffer, "QUIT") == 0) {
			break;
		}

		std::cout << "Enter your message: ";

		std::cin.getline(sendBuffer, 200);
		bytesSent = send(acceptSocket, sendBuffer, 200, 0);
		if (bytesSent == SOCKET_ERROR)
			throw("Server: send() error " + WSAGetLastError());
		else {
			//cout << "Server: send() is OK." << endl;
			// cout << "Server: Bytes Sent: " << bytesSent << endl;
			std::cout << "You sent: " << sendBuffer << std::endl;
		}
	}
}