#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

int main(){
    std::ifstream inputFile("EE.txt"); // Replace "data.txt" with your input file name

    if (!inputFile) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }
           
    std::string line;
    std::map<std::string, std::vector<std::vector<int>>> dataMap;      




}