#ifndef CLIENT_FUNCTIONS_H
#define CLIENT_FUNCTIONS_H

#include <WinSock2.h>

extern int load_WSA_dll(void);
extern SOCKET socket(void);
extern int connectToServer(int port, SOCKET clientSocket);

#endif

