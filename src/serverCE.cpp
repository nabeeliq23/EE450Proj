#include <iostream>
#include "helperFuncs.h"

int main() {
    
    std::string filename = "CE.txt";
    std::map<std::string, std::vector<std::vector<int>>> data = readInput(filename); 
    
    std::cout << "DONE!";

}
