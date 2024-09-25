#include <iostream>
#include <WinSock2.h>
#include "Headers/ClientFunctions.h"

using namespace std;

int main() {

	int port = 55555;
	SOCKET sock;

	load_WSA_dll();
	sock = socket();
	connectToServer(port, sock);


	return 0;
}