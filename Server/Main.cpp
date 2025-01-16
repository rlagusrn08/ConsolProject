#include <iostream>
#include <WinSock2.h>
#include "Game/Game.h"

#pragma comment(lib, "ws2_32.lib") // WinSock2 ���̺귯�� ��ũ

using namespace std;

int main()
{
	CheckMemoryLeak();

    WSADATA wsaData;
    SOCKET hServerSocket;
    SOCKET hClientSocket;
    SOCKADDR_IN serverAddress;
    SOCKADDR_IN clientAddress;
    int iClientAddressSize;

    // DLL �ʱ�ȭ
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }
	
    // ���� ���� ����
    hServerSocket = socket(PF_INET, SOCK_STREAM, 0);
    if(hServerSocket == INVALID_SOCKET) {
        std::cerr << "Socket Error" << std::endl;
        return 1;
    }
    
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(8080); // ��Ʈ 8080

    if (bind(hServerSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cerr << "bind Error" << std::endl;
        return 1;
    }

    if (listen(hServerSocket, 5) == SOCKET_ERROR)
    {
        std::cerr << "listen Error" << std::endl;
        return 1;
    }

    iClientAddressSize = sizeof(clientAddress);
    hClientSocket = accept(hServerSocket, (SOCKADDR*)&clientAddress, &iClientAddressSize);
    if (hClientSocket == INVALID_SOCKET)
    {
        std::cerr << "accept Error" << std::endl;
        return 1;
    }

    char message[] = "Hello World!\n";
    send(hClientSocket, message, sizeof(message), 0);
    closesocket(hClientSocket);
    WSACleanup();
 }