#include <iostream>
#include "helperFuncs.h"

int main() {
    
    std::string filename = "CE.txt";
    std::map<std::string, std::vector<std::vector<int>>> data = readInput(filename); 
    
    std::string key1 = "khloe";
    std::vector<std::vector<int>> stud1 = data[key1];
    
    std::string key2 = "zein";
    std::vector<std::vector<int>> stud2 = data[key2];

    bool isOverlap = classOverlap(stud1, stud2); 
    std::cout << isOverlap; 


    // printData(data);

}
