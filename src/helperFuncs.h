#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> splitString(std::string input, char delimiter){
    std::vector<std::string> tokens; 
    std::istringstream iss(input); 
    std::string token; 

    while(std::getline(iss, token, delimiter)){
        tokens.push_back(token); 
    }

    return tokens; 
}

std::vector<int> parseIntervals(std::string input){
    std::vector<int> numbers; 
    std::string trimmed = input.substr(1); //This step removes opening square bracket
    std::istringstream iss(trimmed); 
    std::string token; 

    while(std::getline(iss, token, ',')){
        numbers.push_back(std::stoi(token));
    }

    return numbers; 
}


std::map<std::string, std::vector<std::vector<int>>> readInput(std::string fileName){
    std::map<std::string, std::vector<std::vector<int>>> dataMap; //Output data structure
    std::ifstream inputFile(fileName); 
    std::string line;

    if(!inputFile){
        std::cerr << "Failed to open file." << std::endl; 
        return dataMap; 
    }          

    while(std::getline(inputFile, line)){
        std::string name; 
        std::vector<std::vector<int>> intervals; 

        //Extract the name by splitting based on semicolon
        std::vector<std::string> parts = splitString(line, ';');
        if(parts.size() == 2){
            name = parts[0];
            std::string intervalsStr = parts[1];

            //Remove the outermost opening and closing brackets
            intervalsStr = intervalsStr.substr(1, intervalsStr.size()-2); 

            //Split the intervals
            std::vector<std::string> intervalTokens = splitString(intervalsStr, ']');
            for(const auto& intervalToken : intervalTokens){
                if(!intervalToken.empty()){
                    std::vector<int> intervalNumbers = parseIntervals(intervalToken);
                    intervals.push_back(intervalNumbers);
                }
            }
        }

        dataMap[name] = intervals; 
    }




         

    return dataMap; 
}

bool classOverlap(std::vector<std::vector<int>> stud1, std::vector<std::vector<int>> stud2){
    return false; 
}