#include <iostream>
#include <WinSock2.h>
#include "Headers/ClientFunctions.h"
#include <thread>

/*
	Steps for Client Functions

	1. Initialize WSA - WSAStartup()
	2. Create a socket - socket()
	3. Connect to the server - connect()
	4. Send and receive data - recv(), send(), recvfrom(), sendto().
	5. Disconnect - closesocket()

*/

using namespace std;

int main() {

	int port = 55555;
	SOCKET sock;
	bool allowedToSend = true;

	load_WSA_dll();
	sock = socket();
	connectToServer(port, sock);

	while (true) {

		thread recieveFromServer(recieveMessages, sock);
		recieveFromServer.detach();

		sendData(sock);

	}
	closesocket(sock);
	WSACleanup();

	return 0;
}