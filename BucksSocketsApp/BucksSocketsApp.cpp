#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include <tchar.h>

using namespace std;

class Data {
public:
	int health;
	char name[50];
};

DWORD WINAPI ServerThreadData(LPVOID lpParam) {
	SOCKET socket = (SOCKET)lpParam;
	int byteCount;
	Data data;
	data.health = 100;
	strcpy_s(data.name, "Master Chief");
	while (1) {
		Sleep(1000);
		if (socket != INVALID_SOCKET) {
			data.health++;
			byteCount = send(socket, (char*)&data, sizeof(Data), 0);
			if (byteCount == SOCKET_ERROR) {
				cout << "Server send error " << WSAGetLastError() << endl;
				closesocket(socket);
				return -1;
			}
			else {
				cout << "Server: sent " << byteCount << " bytes" << endl;
			}
		}
	}
	closesocket(socket);
	return 0;
}


DWORD WINAPI ServerThread(LPVOID lpParam) {
	SOCKET socket = (SOCKET)lpParam;
	int byteCount;
	char buffer[200] = "";
	while (1) {
		if (socket != INVALID_SOCKET) {
			// Block until data received
			byteCount = recv(socket, buffer, 200, 0);
			if (byteCount == SOCKET_ERROR) {
				cout << "Connection closed" << endl;
				return -1;
			}
			// Client connection was closed
			if (byteCount == 0) {
				shutdown(socket, SD_SEND);
				closesocket(socket);
				socket = INVALID_SOCKET;
				return -1;
			}
			else {
				cout << "From Client : " << buffer << endl;
				char sendBuffer[200] = "Message Received";
				byteCount = send(socket, sendBuffer, 200, 0);
				if (byteCount == SOCKET_ERROR) {
					cout << "Server send error " << WSAGetLastError() << endl;
					closesocket(socket);
					return -1;
				}
				else {
					cout << "Server: sent " << byteCount << endl;
				}
			}
		}
	}
	closesocket(socket);
	return 0;
}

int main(int argc, char* argv[]) {
	SOCKADDR_STORAGE from;
	int retval, fromlen, socket_type;
	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];


	SOCKET serverSocket, acceptSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "The Winsock dll not found!" << endl;
		return 0;
	}
	else {
		cout << "The Winsock dll found!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;
	}

	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is OK!" << endl;
	}


	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "bind() failed: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		cout << "bind() is OK!" << endl;
	}

	if (listen(serverSocket, 1) == SOCKET_ERROR)
		cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
	else
		cout << "listen() is OK, I'm waiting for connections..." << endl;


	/* Comment out for Exercise 5
	fromlen = sizeof(socket_type);
	retval = getsockopt(serverSocket, SOL_SOCKET, SO_TYPE, (char *)&socket_type, &fromlen);
	fromlen = sizeof(from);
	acceptSocket = accept(serverSocket, (SOCKADDR *)&from, &fromlen);

	//acceptSocket = accept(serverSocket, NULL,NULL);
	if (acceptSocket == INVALID_SOCKET){
		cout <<  "accept failed: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	retval = getnameinfo((SOCKADDR *)&from,
					  fromlen,
					  hoststr,
					  NI_MAXHOST,
					  servstr,
					  NI_MAXSERV,
					  NI_NUMERICHOST | NI_NUMERICSERV);
	if (retval != 0){
			 cout <<  "getnameinfo failed: " << retval << endl;
			WSACleanup();
			 return -1;
	}
	cout << "Accepted connection from host " <<  hoststr << " and port " << servstr << endl;
	cout << "Accepted connection" << endl;
	*/


	/*
		// Exercise 1
		int bytesSent;
		char buffer[200]= "";
		int bytesRecv = SOCKET_ERROR;
		bytesRecv = recv(acceptSocket, buffer, 200, 0);
		if (bytesRecv == SOCKET_ERROR)
			cout << "Server: recv() error " << WSAGetLastError() << endl;
		else{
			cout << "Server: recv() is OK." << endl;
			cout << "Server: Received data is: " <<  buffer << endl;
			cout << "Server: Bytes received: " << bytesRecv << endl;
		}

		// Exercise 2
		char sendBuffer[200] = "Message Received";
		cout << "Server: Sending some test data to client..." << endl;
		bytesSent = send(acceptSocket, sendBuffer, strlen(sendBuffer), 0);
		if (bytesSent == SOCKET_ERROR)
			cout << "Server: send() error " << WSAGetLastError() << endl;
		else{
			cout << "Server: send() is OK." << endl;
			cout << "Server: Bytes Sent: " << bytesSent << endl;
		}
	*/
	/*
		// Exercise 3
		int bytesSent;
		int bytesRecv = SOCKET_ERROR;
		char buffer[200]= "";
		while(1){
			bytesRecv = recv(acceptSocket, buffer, 200, 0);
			if (bytesRecv == SOCKET_ERROR)
				cout << "Server: recv() error " << WSAGetLastError() << endl;
			else{
				cout << "Server: recv() is OK." << endl;
				cout << "Server: Received data is: " <<  buffer << endl;
				cout << "Server: Bytes received: " << bytesRecv << endl;
			}

			char sendBuffer[200] = "Message Received";

			cout << "Server: Sending some test data to client..." << endl;
			bytesSent = send(acceptSocket, sendBuffer, strlen(sendBuffer), 0);
			if (bytesSent == SOCKET_ERROR)
				cout << "Server: send() error " << WSAGetLastError() << endl;
			else{
				cout << "Server: send() is OK." << endl;
				cout << "Server: Bytes Sent: " << bytesSent << endl;
			}
		}
	*/
	/*
	// Exercise 4
	int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	char buffer[200]= "";
	while(1){
		bytesRecv = recv(acceptSocket, buffer, 200, 0);
		if (bytesRecv == SOCKET_ERROR)
			cout << "Server: recv() error " << WSAGetLastError() << endl;
		else{
			cout << "Server: recv() is OK." << endl;
			cout << "Server: Received data is: " <<  buffer << endl;
			cout << "Server: Bytes received: " << bytesRecv << endl;
		}

		if (strcmp(buffer,"SHUTDOWN")== 0){
			break;
		}


		char sendBuffer[200] = "Message Received";

		cout << "Server: Sending some test data to client..." << endl;
		bytesSent = send(acceptSocket, sendBuffer, strlen(sendBuffer), 0);
		if (bytesSent == SOCKET_ERROR)
			cout << "Server: send() error " << WSAGetLastError() << endl;
		else{
			cout << "Server: send() is OK." << endl;
			cout << "Server: Bytes Sent: " << bytesSent << endl;
		}
	}
*/

// Exercise 5
	DWORD threadId;
	while (1) {
		acceptSocket = accept(serverSocket, NULL, NULL);
		if (acceptSocket == INVALID_SOCKET) {
			cout << stderr << " accept failed: " << WSAGetLastError() << endl;
			return -1;
		}
		else {
			cout << "Server: Client Connected!" << endl;
			// CreateThread(NULL,0,ServerThread,(LPVOID)acceptSocket,0,&threadId);
			// Exercise 6
			CreateThread(NULL, 0, ServerThreadData, (LPVOID)acceptSocket, 0, &threadId);
		}
	}
	system("pause");
	WSACleanup();


	return 0;
}