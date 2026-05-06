#include <iostream>
#include <winsock2.h>
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

// Background thread function to listen for messages
void receive_messages(SOCKET s) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, 1024);
        int bytes = recv(s, buffer, 1024, 0);
        
        if (bytes <= 0) {
            cout << "\n\033[1;31m[!] Connection lost with Anonymous 1.\033[0m" << endl;
            exit(0);
        }
        
        // Output format: [Sender Name]: Message Content
        cout << "\n\033[1;32m[Anonymous 1]: \033[0m" << buffer << "\n\033[1;36m[Anonymous 2 (You)]: \033[0m" << flush;
    }
}

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;

    WSAStartup(MAKEWORD(2, 2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Define Server details
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(5555);

    // Attempt to connect to Anonymous 1
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        cout << "[!] Anonymous 1 is not reachable. Ensure the server is running." << endl;
        return 1;
    }

    cout << "\033[1;36m--- Encrypted Channel Established ---\033[0m" << endl;

    // Start a thread to handle incoming data separately
    thread receive_thread(receive_messages, s);
    receive_thread.detach();

    // Main loop for sending data
    while (true) {
        string msg;
        cout << "\033[1;36m[Anonymous 2 (You)]: \033[0m";
        getline(cin, msg);
        
        if (msg == "exit") break;
        send(s, msg.c_str(), msg.length(), 0);
    }

    closesocket(s);
    WSACleanup();
    return 0;
}