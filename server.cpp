#include <iostream>
#include <winsock2.h>
#include <string>
#include <thread> // Required for handling multiple flows of execution

#pragma comment(lib, "ws2_32.lib")
using namespace std;

// Function to handle incoming messages in the background
void receive_messages(SOCKET s) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, 1024);
        int bytes = recv(s, buffer, 1024, 0);
        
        if (bytes <= 0) {
            cout << "\n\033[1;31m[!] Connection lost with Anonymous 2.\033[0m" << endl;
            exit(0);
        }
        
        // Print received message and reset the prompt line
        cout << "\n\033[1;35m[Anonymous 2]: \033[0m" << buffer << "\n\033[1;32m[Anonymous 1 (You)]: \033[0m" << flush;
    }
}

int main() {
    WSADATA wsa;
    SOCKET s, client_sock;
    struct sockaddr_in server, client;
    int c = sizeof(struct sockaddr_in);

    // Initialize Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // Listen on all available interfaces
    server.sin_port = htons(5555);

    // Bind the socket
    bind(s, (struct sockaddr *)&server, sizeof(server));
    
    // Listen for incoming connections
    listen(s, 3);

    cout << "\033[1;33m[*] Anonymous 1 is online. Waiting for Anonymous 2...\033[0m" << endl;
    client_sock = accept(s, (struct sockaddr *)&client, &c);
    cout << "\033[1;32m[+] Anonymous 2 joined the encrypted channel.\033[0m" << endl;

    // Launch receiving thread (Asynchronous)
    thread receive_thread(receive_messages, client_sock);
    receive_thread.detach(); 

    // Main thread handles outgoing messages
    while (true) {
        string msg;
        cout << "\033[1;32m[Anonymous 1 (You)]: \033[0m";
        getline(cin, msg);
        
        if (msg == "exit") break;
        send(client_sock, msg.c_str(), msg.length(), 0);
    }

    closesocket(client_sock);
    WSACleanup();
    return 0;
}