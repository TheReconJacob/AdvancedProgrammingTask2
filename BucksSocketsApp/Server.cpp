#include "Server.h"
#include <iostream>
#include <tchar.h>
#include <WS2tcpip.h>

DWORD WINAPI Server::ServerThread(LPVOID lpParam) {
	Comms* comms = new Comms;
	Server* server = new Server;
	serverSocket = (SOCKET)lpParam;
	int byteCount;
	char buffer[200] = "";
	while (1) {
		if (serverSocket != INVALID_SOCKET) {
			// Block until data received
			byteCount = recv(serverSocket, buffer, 200, 0);
			if (byteCount == SOCKET_ERROR) {
				std::cout << "Connection closed" << std::endl;
				return -1;
			}
			// Client connection was closed
			if (byteCount == 0) {
				shutdown(serverSocket, SD_SEND);
				closesocket(serverSocket);
				serverSocket = INVALID_SOCKET;
				return -1;
			}
			else {
				std::cout << "From Client : " << buffer << std::endl;
				char sendBuffer[200] = "Message Received";
				byteCount = send(serverSocket, sendBuffer, 200, 0);
				if (byteCount == SOCKET_ERROR) {
					std::cout << "Server send error " << WSAGetLastError() << std::endl;
					closesocket(serverSocket);
					return -1;
				}
				else {
					std::cout << "Server: sent " << byteCount << std::endl;
				}
			}
		}
	}
	closesocket(serverSocket);
	return 0;
}
int Server::WsaerrCheck()
{
	if (wsaerr != 0) {
		std::cout << "The Winsock dll not found!" << std::endl;
		return 0;
	}
	else {
		std::cout << "The Winsock dll found!" << std::endl;
		std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
	}
}

int Server::ServerSocketSetup()
{
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "socket() is OK!" << std::endl;
	}
}

int Server::ServerServiceSetup()
{
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "bind() is OK!" << std::endl;
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR)
		std::cout << "listen(): Error listening on socket " << WSAGetLastError() << std::endl;
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
			std::cout << "Server: recv() error " << WSAGetLastError() << std::endl;
		else {
			//cout << "Server: recv() is OK." << endl;
			std::cout << "From Client: " << buffer << std::endl;
			//cout << "Server: Bytes received: " << bytesRecv << endl;
		}

		if (strcmp(buffer, "QUIT") == 0) {
			break;
		}


		char sendBuffer[200];

		std::cout << "Enter your message: ";

		std::cin.getline(sendBuffer, 200);
		bytesSent = send(acceptSocket, sendBuffer, strlen(sendBuffer), 0);
		if (bytesSent == SOCKET_ERROR)
			std::cout << "Server: send() error " << WSAGetLastError() << std::endl;
		else {
			//cout << "Server: send() is OK." << endl;
			// cout << "Server: Bytes Sent: " << bytesSent << endl;
			std::cout << "You sent: " << sendBuffer << std::endl;
		}
	}
}