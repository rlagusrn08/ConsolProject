#include "NetworkExample.h"

#include <iostream>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // WinSock2 라이브러리 링크

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

    // 서버 소켓 생성
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET) {
        std::cerr << "Socket Error" << std::endl;
        return 1;
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    InetPton(AF_INET, TEXT("127.0.0.1"), &serverAddress.sin_addr.s_addr);
    //serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // local
    serverAddress.sin_port = htons(8080); // 포트 8080

    //연결 요청
    if (connect(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cerr << "Connect Error" << std::endl;
        return 1;
    }

    //데이터 수신
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
