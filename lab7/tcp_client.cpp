#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    WSAStartup(ver, &data);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54001);
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

    int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR) {
        cout << "Can't connect to server!" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    char buf[4096];
    string userInput;

    while (true) {
        cout << "> ";
        getline(cin, userInput);

        if (userInput == "exit") {
            send(sock, userInput.c_str(), userInput.size() + 1, 0);
            break;
        }

        if (userInput.size() > 0) {
            int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
            if (sendResult != SOCKET_ERROR) {
                ZeroMemory(buf, 4096);
                int bytesReceived = recv(sock, buf, 4096, 0);
                if (bytesReceived > 0) {
                    cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
                }
            }
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}