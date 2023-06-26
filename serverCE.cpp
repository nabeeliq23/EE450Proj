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
#include "helperFuncs.h"


const int MAIN_SERVER_UDP_PORT = 23370;
const int CE_SERVER_UDP_PORT = 21370; 
const int BUFFER_SIZE = 1024;

using namespace std;

int main() {

    std::cout << "ServerCE is up and running using UDP " 
                 "on Port " + std::to_string(CE_SERVER_UDP_PORT) << 
                  std::endl; 

    // Read in Data
    std::string filename = "CE.txt";
    std::map<std::string, std::vector<std::vector<int>>> data = readInput("CE.txt"); 
    
    // Create UDP socket
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udpSocket == -1){
        std::cerr << "Failed to create UDP socket." << std::endl; 
        return 1; 
    }

    // Setup client Address
    sockaddr_in clientAddress{};
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddress.sin_port = htons(CE_SERVER_UDP_PORT);

    // Bind the client socket to the specified port
    if(bind(udpSocket, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) < 0) {
        std::cerr << "Failed to bind UDP socket." << std::endl; 
        close(udpSocket);
        return 1; 
    }

    // Set up server Address
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(MAIN_SERVER_UDP_PORT);
    
    // Convert names to a single string
    string names = "";
    map<string,vector<vector<int>>> :: iterator it;
    for(it = data.begin(); it != data.end(); it++){
        if(it != data.end()){
            names += it->first + " ";
        } else {
            names += it->first;
        }
    }
    
    // Send names
    if(sendto(udpSocket, names.c_str(), names.size(), 0,
    (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        std::cerr << "Failed to send UDP data." << std::endl; 
        close(udpSocket); 
        return 1; 
    }

    std::cout << "ServerCE  finished  sending  a  list  of "
                 "usernames  to  Main  Server. " << std::endl;  


    while(1){
        char CEnames[BUFFER_SIZE]; 
        memset(CEnames, 0, sizeof(CEnames));
        sockaddr_in senderAddress{}; 
        socklen_t senderAddressLength = sizeof(senderAddress);
        ssize_t udpBytesReceived = recvfrom(udpSocket, CEnames, sizeof(CEnames), 0, 
                                (struct sockaddr *)&senderAddress, &senderAddressLength);

        if (udpBytesReceived == -1){
            std::cerr << "Failed to receive UDP data from client 2." << std::endl;
            return 1; 
        }
        cout << "Names receieved from main server: " << CEnames << endl;
    }

    // Close the UDP Socket
    close(udpSocket); 

    // std::string filename = "CE.txt";
    // std::map<std::string, std::vector<std::vector<int>>> data = readInput(filename); 
    
    // std::string key1 = "khloe";
    // std::vector<std::vector<int>> stud1 = data[key1];
    
    // std::string key2 = "zein";
    // std::vector<std::vector<int>> stud2 = data[key2];

    // bool isOverlap = classOverlap(stud1, stud2); 
    // std::cout << isOverlap; 


    // printData(data);

}
