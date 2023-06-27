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
#include <vector>
//#include <cstring>
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
        std::string name = CEnames;
        std::vector<string> CEvector   = splitString(name, " "); 

        std::string response = " do not exist.";

        if(CEvector.size() == 2){
            std::vector<std::vector<int>> stud1 = data[CEvector[0]];
            std::vector<std::vector<int>> stud2 = data[CEvector[1]];   
            bool isOverlap = classOverlap(stud1, stud2);
            response = "Found " + CEvector[0] + "," + CEvector[1] + " located at CE.\n";

            if(isOverlap){
                response += "Main Server received from server CE the intersection result using UDP over port (CEPort)";
            } else {
                response += "No overlap found between these names.";
            }
            
            if(sendto(udpSocket, response.c_str(), response.size(), 0,
                (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
                std::cerr << "Failed to send UDP data." << std::endl; 
                close(udpSocket); 
                return 1; 
            }
        } else {
            response = "Found " + CEvector[0] + " located at CE.::";
            
            std::string intervals = "["; 
            std::string key = CEvector[0];
            std::vector<std::vector<int>> stud = data[key];

            size_t totalElements = stud.size(); 
            size_t currentIteration = 0; 
            
            for(const auto& range: stud){
                ++currentIteration; 

                intervals += "["; 
                intervals += std::to_string(range[0]); 
                intervals += ",";
                intervals += std::to_string(range[1]); 
                intervals += "]";

                if(currentIteration != totalElements){
                    intervals += ",";
                } else {
                    intervals += "]::"; 
                }
            }

            response += intervals; 
            std::cout << "Response split case: " << response << std::endl; 

            if(sendto(udpSocket, response.c_str(), response.size(), 0,
                (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
                std::cerr << "Failed to send UDP data." << std::endl; 
                close(udpSocket); 
                return 1; 
            }
          
        }
        
       
        
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
