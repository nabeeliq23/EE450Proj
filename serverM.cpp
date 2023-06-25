#include <iostream>
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

#define MAIN_SERVER_PORT 24370

// bool keepRunning = true; 

int main() {
     
    //Create TCP socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
    if(serverSocket == -1){
        std::cerr << "Failed to create socket." << std::endl; 
        return 1; 
    }

    //Setup Server Address 
    sockaddr_in serverAddress{}; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(MAIN_SERVER_PORT); 

    //Bind Socket to the specified Address
    if(bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        std::cerr << "Binding failed." << std::endl; 
        return 1; 
    }

    // Listen for incoming connections
    if(listen(serverSocket, 1) < 0){
        std::cerr << "Listening Failed." << std::endl; 
    }

    std::cout << "Server Listening" << std::endl; 

    //Accept a client connection 
    int clientSocket; 
    sockaddr_in clientAddress{}; 
    socklen_t clientAddressLength = sizeof(clientAddress); 

    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if(clientSocket < 0){
        std::cerr << "Failed to accept client connection." << std::endl; 
        close(serverSocket); 
        return 1; 
    }

    std::cout << "Client connected." << std::endl; 

   while(1){
        //Client Request
        char buffer[1024] = {0}; 
        int bytesRead = read(clientSocket, buffer, 1024); 

        //Process client request
        std::string response; 
        if(bytesRead > 0){
            std::string request(buffer); 
            response = "Recieved request: " + request; 
            std::cout << "Received request from client: " << request << std::endl; 
        } else {
            response = "Error: Failed to read client message";
        }
        // Send the response to the client
        send(clientSocket, response.c_str(), response.size(), 0); 
        std::cout << "Sent response" << std::endl;
   } 

    return 0;
}
