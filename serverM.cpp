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
#include  <vector>
#include "helperFuncs.h"

const int MAIN_SERVER_UDP_PORT = 23370;
const int MAIN_SERVER_TCP_PORT = 24370;
const int BUFFER_SIZE = 1024;
  

int main() {
     
     std::cout << "Main server is up and running." << std::endl; 

    //Create TCP socket
    int tcpSocket = socket(AF_INET, SOCK_STREAM, 0); 
    if(tcpSocket == -1){
        std::cerr << "Failed to create socket." << std::endl; 
        return 1; 
    }

    //Create UDP socket
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udpSocket == -1){
        std::cerr << "Failed to create UDP socket." << std::endl; 
        return 1; 
    }

    //Setup TCP Server Address 
    sockaddr_in tcpAddress{}; 
    tcpAddress.sin_family = AF_INET; 
    tcpAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    tcpAddress.sin_port = htons(MAIN_SERVER_TCP_PORT); 

    //Setup UDP Server Address 
    sockaddr_in udpAddress{}; 
    udpAddress.sin_family = AF_INET; 
    udpAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    udpAddress.sin_port = htons(MAIN_SERVER_UDP_PORT);


    //Bind Socket to the specified Address
    if(bind(tcpSocket, (struct sockaddr *)&tcpAddress, sizeof(tcpAddress)) < 0){
        std::cerr << "Binding failed." << std::endl; 
        return 1; 
    }

    //Bind Socket to the specified Address
    if(bind(udpSocket, (struct sockaddr *)&udpAddress, sizeof(udpAddress)) < 0){
        std::cerr << "Binding failed." << std::endl; 
        return 1; 
    }

    //Recieve and print UDP data from client 1
    char CEnames[BUFFER_SIZE]; 
    memset(CEnames, 0, sizeof(CEnames));
    sockaddr_in senderAddress1{}; 
    socklen_t senderAddressLength1 = sizeof(senderAddress1);
    ssize_t udpBytesReceived1 = recvfrom(udpSocket, CEnames, sizeof(CEnames), 0, 
                                (struct sockaddr *)&senderAddress1, &senderAddressLength1);

    if (udpBytesReceived1 == -1){
        std::cerr << "Failed to receive UDP data from client 1." << std::endl;
        return 1; 
    }

    std::cout << "Main server received names from server CE using UDP" 
                 " over Port " + std::to_string(MAIN_SERVER_UDP_PORT) << std::endl; 

    std::string CEnames1 = CEnames; 
    std::vector<std::string> CEserverNames = splitString(CEnames1, " ");   

    //Receive and print UDP data from client 2
    char EEnames[BUFFER_SIZE]; 
    memset(EEnames, 0, sizeof(EEnames));
    sockaddr_in senderAddress2{}; 
    socklen_t senderAddressLength2 = sizeof(senderAddress2);
    ssize_t udpBytesReceived2 = recvfrom(udpSocket, EEnames, sizeof(EEnames), 0, 
                                (struct sockaddr *)&senderAddress2, &senderAddressLength2);

    if (udpBytesReceived2 == -1){
        std::cerr << "Failed to receive UDP data from client 2." << std::endl;
        return 1; 
    }

    std::cout << "Main server received names from server EE using UDP" 
                 " over Port " + std::to_string(MAIN_SERVER_UDP_PORT) << std::endl;

    std::string EEnames1 = EEnames; 
    std::vector<std::string> EEserverNames = splitString(EEnames1, " ");

    // Listen for incoming connections
    if(listen(tcpSocket, 1) < 0){
        std::cerr << "Listening Failed." << std::endl; 
    }

    std::cout << "Server Listening" << std::endl; 

    //Accept a client connection 
    int clientSocket; 
    sockaddr_in clientAddress{}; 
    socklen_t clientAddressLength = sizeof(clientAddress); 

    clientSocket = accept(tcpSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if(clientSocket < 0){
        std::cerr << "Failed to accept client connection." << std::endl; 
        close(tcpSocket); 
        return 1; 
    }

    std::cout << "Client connected." << std::endl; 

    //Init Variables
    char tcpBuffer[BUFFER_SIZE];
    ssize_t tcpBytesReceived; 
    std::string clientNames;
    std::vector<std::string> studNames;
    std::string CEsend = ""; 
    std:: string EEsend = "";

   while(1){
        
        memset(tcpBuffer, 0, sizeof(tcpBuffer)); 
        tcpBytesReceived = recv(clientSocket, tcpBuffer, sizeof(tcpBuffer), 0); 
        if(tcpBytesReceived == -1){
            std::cerr << "Failed to receive TCP data." << std::endl; 
            return 1; 
        }
        
        //Take client name and seperate into two
        clientNames = tcpBuffer; 
        studNames   = splitString(clientNames, " ");

        for(int i = 0; i < studNames.size(); i++){
            std::string currName = studNames[i]; 

            if(std::find(CEserverNames.begin, CEServerNames.end(), currName)!= CEserverNames.end()){
                CEsend += currName + " "; 
            }

            if(std::find(EEserverNames.begin, EEserverNames.end(), currName)!= EEserverNames.end()){
                EEsend += currName + " "; 
            }

        }
        
        

        std::cout << "TCP Data: " << tcpBuffer << std::endl; 
        
   } 

    return 0;
}
