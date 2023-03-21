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



int _tmain(int argc, _TCHAR* argv[]) {
	SOCKET clientSocket;
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

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "socket() is OK!" << endl;
	}

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		cout << "Client: connect() - Failed to connect." << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "Client: connect() is OK." << endl;
		cout << "Client: Can start sending and receiving data..." << endl;
	}


		// Exercise
		int byteCount = SOCKET_ERROR;
		char buffer[200];
		while(1){
			cout << "Enter your message: ";
			cin.getline(buffer,200);
			byteCount = send(clientSocket, buffer, 200, 0);
			if(byteCount == SOCKET_ERROR){
				cout << "Client: send() error " <<  WSAGetLastError() << endl;
			}
			else{
				//cout << "Client: sent " <<  byteCount << " bytes" << endl;
				cout << "You sent: " << buffer << endl;
				if (strcmp(buffer,"QUIT")== 0){
					break;
				}
			}

			char receiveBuffer[200]="";
			byteCount = recv(clientSocket, receiveBuffer, 200, 0);
			if (byteCount == 0 || byteCount == WSAECONNRESET){
				cout << "Client: Connection Closed." << endl;
			}
			if (byteCount < 0){
				cout << "Client: error " << WSAGetLastError() << endl;
			}
			else {
				cout << "From Server: " << receiveBuffer << endl;
			}
		}


	system("pause");
	WSACleanup();
	return 0;

}
