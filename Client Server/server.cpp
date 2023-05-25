#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

constexpr int MAX_CLIENTS = 5;
constexpr int BUFFER_SIZE = 2048;

void clientHandler(SOCKET clientSocket) {
    char buffer[BUFFER_SIZE];
    int bytesRead;
    std::cout<<"Connected to socket: "<<clientSocket<<std::endl;
    do {
        bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::cout << "Received message from client (socket ID "<<clientSocket<<"): " << buffer << std::endl;
            buffer[bytesRead] = '!';
            buffer[bytesRead+1] = '\n';
            // Echo the message back to the client
            send(clientSocket, buffer, bytesRead+1, 0);
        }
    } while (bytesRead > 0);

    // Close the client socket
    closesocket(clientSocket);
    std::cout << "Client disconnected" << std::endl;
}

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return -1;
    }

    // Create server socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Failed to create socket" << std::endl;
        WSACleanup();
        return -1;
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(12345);

    // Bind the server socket to the specified IP and port
    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind the socket to IP and port" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, MAX_CLIENTS) == SOCKET_ERROR) {
        std::cerr << "Failed to listen for connections" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Server started. Listening for connections..." << std::endl;

    socklen_t clientAddressLength = sizeof(clientAddress);

    // Accept client connections
    while (true) {
        if ((clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddress, &clientAddressLength)) == INVALID_SOCKET) {
            std::cerr << "Failed to accept client connection" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return -1;
        }

        std::cout << "New client connected" << std::endl;

        // Create a new thread to handle the client connection
        std::thread clientThread(clientHandler, clientSocket);

        clientThread.detach();
    }

    // Cleanup and close the server socket
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
