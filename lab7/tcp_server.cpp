#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0) {
        cout << "Can't Initialize winsock! Quitting" << endl;
        return 1;
    }

    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54001); // Другой порт для TCP
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(listening, (sockaddr*)&hint, sizeof(hint));
    listen(listening, SOMAXCONN);

    cout << "TCP Server started. Waiting for connection..." << endl;

    sockaddr_in client;
    int clientSize = sizeof(client);
    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    closesocket(listening);

    char buf[4096];

    while (true) {
        ZeroMemory(buf, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        
        if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
            cout << "Client disconnected" << endl;
            break;
        }

        string msg(buf, 0, bytesReceived);
        cout << "Client: " << msg << endl;

        if (msg == "exit") break; // Условие выхода

        // Отправляем обратно (эхо)
        send(clientSocket, buf, bytesReceived + 1, 0);
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}