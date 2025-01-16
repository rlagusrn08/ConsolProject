#include "NetworkExample.h"

#include <iostream>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // WinSock2 ���̺귯�� ��ũ

int NetworkExample::Example()
{
    WSADATA wsaData;
    SOCKET hSocket;
    char message[30];
    int strLen;
    SOCKADDR_IN serverAddress;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // ���� ���� ����
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET) {
        std::cerr << "Socket Error" << std::endl;
        return 1;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    InetPton(AF_INET, TEXT("127.0.0.1"), &serverAddress.sin_addr.s_addr);
    //serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // local
    serverAddress.sin_port = htons(8080); // ��Ʈ 8080

    //���� ��û
    if (connect(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cerr << "Connect Error" << std::endl;
        return 1;
    }

    //������ ����
    strLen = recv(hSocket, message, sizeof(message) - 1, 0);
    if (strLen == -1)
    {
        std::cerr << "Read Error" << std::endl;
        return 1;
    }

    message[strLen] = '\0';
    std::cout << "Message from server : " << message << '\n';

    closesocket(hSocket);
    WSACleanup();
}
