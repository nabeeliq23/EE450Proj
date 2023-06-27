#include <iostream>
#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <errno.h>
#include  <string.h>
#include  <netdb.h>
#include  <sys/types.h>
#include  <netinet/in.h>
#include  <sys/socket.h>
#include  <arpa/inet.h>
#include  <sys/wait.h>
#include  <signal.h>

const int MAIN_SERVER_PORT = 24370; 
#define MAIN_SERVER_IP "127.0.0.1"

int main() {

    // Create a TCP connection
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1){
        std::cerr << "Failed to create client socket." << std::endl;
        return 1;
    }

    // Bind client socket dynamically to a port
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddress.sin_port = 0; //Dynamic Allocation
    if(bind(clientSocket, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) < 0){
        std::cerr << "Binding failed." << std::endl;
        return 1;
    }

    // Get the allocated port
    if(getsockname(clientSocket, (struct sockaddr *)&clientAddress, &clientAddressLength) < 0){
        std::cerr << "Failed to get the allocated port." << std::endl;
        return 1;
    }
    int clientPort = ntohs(clientAddress.sin_port);

    // Server Setup
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(MAIN_SERVER_PORT);
    if(inet_pton(AF_INET, MAIN_SERVER_IP, &(serverAddress.sin_addr)) <= 0){
        std::cerr << "Invalid address." << std::endl;
    }

    // Connect to the main server
    if(connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed." << std::endl;
        return 1;
    }


    //Continue asking users for input
    while(1) {
        //Send request to main server
        std::string request;
        std::cout << "Please enter the usernames to check the common course selection:";
        std::getline(std::cin, request);
        if(request.empty()){
            continue;
        }

        send(clientSocket, request.c_str(), request.size(), 0);

        // Receive response from main server
        char buffer[1024] = "";
        int bytesRead = read(clientSocket, buffer, 1024);
        std::cout << "Response from main server: " << buffer << std::endl;

    }

    return 0;
}
