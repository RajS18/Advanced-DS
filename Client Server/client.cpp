#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

constexpr int BUFFER_SIZE = 2048;

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddress;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return -1;
    }

    // Create client socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Failed to create socket" << std::endl;
        WSACleanup();
        return -1;
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(12345);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to the server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return -1;
    }

    char buffer[BUFFER_SIZE];
    std::string message;

    // Send and receive messages
    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);

        // Send the message to the server
        send(clientSocket, message.c_str(), message.length(), 0);

        // Receive the echoed message from the server
        int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesRead <= 0) {
            break;
        }
        std::cout<<bytesRead<<std::endl;
        buffer[bytesRead] = '\0';
        std::cout << "Received echoed message from server: " << buffer << std::endl;
    }

    // Close the client socket
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
