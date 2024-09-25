#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Headers/ClientFunctions.h"
#include <tchar.h>

using namespace std;

/*
	WSADATA struct:

	typedef struct WSAData{
		WORD wVersion;         // Winsock version
		WORD wHighVersion;     // Highest version supported
		char szDescription[WSADESCRIPTION_LEN + 1];  // Description of the Winsock implementation
		char szSystemStatus[WSASYSSTATUS_LEN + 1];   // Status or configuration string
		unsigned short iMaxSockets;  // Maximum number of sockets allowed
		unsigned short iMaxUdpDg;    // Maximum size of a UDP datagram
		char* lpVendorInfo;          // Vendor-specific information
	}

*/

// Load the Windows Socket API dll file
int load_WSA_dll(void) {

	WSADATA wsaData;	// WSASdata struct
	int wsaErr;			// WSA Error, if the startup dosent return 0

												// Combines two 8-bit values into as single 16 bit value
	WORD wVersionRequested = MAKEWORD(2, 2);	// (2,2) represents Winsock version 2.2
	wsaErr = WSAStartup(wVersionRequested, &wsaData);

	// if WSAStartup is successfull then it will return 0
	if (wsaErr != 0) {
		cout << "Winsock dll not found!" << endl;
		return 0;
	}
	else {
		cout << "The Winsock dll found!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;
	}

	return 0;
}

// Creates a socket 
SOCKET socket(void) {

	SOCKET clientSocket = socket(AF_INET,		// af (address family): 'AF_INET' means for UDP or TCP
								SOCK_STREAM,	// type: SOCK_STREAM for TCP and SOCK_DGRAM for UDP
								IPPROTO_TCP);	// protocol: IPPROTO_TCP for TCP

	if (clientSocket == INVALID_SOCKET) {

		cerr << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		closesocket(clientSocket);	// close the socket
		return 0;
	}
	else {
		cout << "socket() is OK!" << endl;
	}

	return clientSocket;
}

int connectToServer( int port, SOCKET clientSocket) {

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
		cout << "Client: Connect() is OK." << endl;
		cout << "Client: can start sending and recieving data" << endl;
	}
}