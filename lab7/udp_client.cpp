#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA data;
    int wsOk = WSAStartup(MAKEWORD(2, 2), &data);
    if (wsOk != 0) {
        cout << "Can't start Winsock! " << wsOk << endl;
        return 1;
    }

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

    string msg = "";
    while (true) {
        cout << "> ";
        getline(cin, msg);

        if (msg == "exit") break; // Условие выхода

        int sendOk = sendto(out, msg.c_str(), msg.size() + 1, 0, (sockaddr*)&server, sizeof(server));
        if (sendOk == SOCKET_ERROR) {
            cout << "That didn't work! " << WSAGetLastError() << endl;
        }
    }

    closesocket(out);
    WSACleanup();
    return 0;
}