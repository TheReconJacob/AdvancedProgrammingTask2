#include "Client.h"
#include <ws2tcpip.h>
#include <iostream>
#include <tchar.h>

int Client::WsaerrCheck()
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

int Client::ClientSocketSetup()
{
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "socket() is OK!" << std::endl;
	}
}

int Client::ClientServiceSetup()
{
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		std::cout << "Client: connect() - Failed to connect." << std::endl;
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "Client: connect() is OK." << std::endl;
		std::cout << "Client: Can start sending and receiving data..." << std::endl;
	}
}

void Client::SendAndReceiveFromServer()
{
	int byteCount = SOCKET_ERROR;
	char buffer[200];
	while (1) {
		std::cout << "Enter your message: ";
		std::cin.getline(buffer, 200);
		byteCount = send(clientSocket, buffer, 200, 0);
		if (byteCount == SOCKET_ERROR) {
			std::cout << "Client: send() error " << WSAGetLastError() << std::endl;
		}
		else {
			//cout << "Client: sent " <<  byteCount << " bytes" << endl;
			std::cout << "You sent: " << buffer << std::endl;
			if (strcmp(buffer, "QUIT") == 0) {
				break;
			}
		}

		char receiveBuffer[200] = "";
		byteCount = recv(clientSocket, receiveBuffer, 200, 0);
		if (byteCount == 0 || byteCount == WSAECONNRESET) {
			std::cout << "Client: Connection Closed." << std::endl;
		}
		if (byteCount < 0) {
			std::cout << "Client: error " << WSAGetLastError() << std::endl;
		}
		else {
			std::cout << "From Server: " << receiveBuffer << std::endl;
		}
	}
}