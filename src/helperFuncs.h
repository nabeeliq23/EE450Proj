#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> splitString(std::string input, const std::string& delimiter){
    std::vector<std::string> tokens; 
    std::size_t startPos = 0; 
    std::size_t delimiterPos = input.find(delimiter);
    
    while(delimiterPos != std::string::npos){
        std::string token = input.substr(startPos, delimiterPos - startPos);
        if(!token.empty()){
            tokens.push_back(token);
        }

        startPos = delimiterPos + delimiter.length();
        delimiterPos = input.find(delimiter, startPos);
    }

    std::string lastToken = input.substr(startPos); 
    if(!lastToken.empty()){
        tokens.push_back(lastToken); 
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
        std::string nameSplit = ";"; 
        std::vector<std::string> parts = splitString(line, nameSplit);
        if(parts.size() == 2){
            name = parts[0];
            std::string intervalsStr = parts[1];

            //Remove the outermost opening and closing brackets
            intervalsStr = intervalsStr.substr(1, intervalsStr.size()-3); 

            //Split the intervals
            std::string intervalSplit = "],";
            std::vector<std::string> intervalTokens = splitString(intervalsStr, intervalSplit);
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

void printData(std::map<std::string, std::vector<std::vector<int>>> dataMap){
    for(const auto& entry : dataMap){
        std::cout << "Name:" << entry.first; 
        std::cout << " Intervals:";
        for(const auto& interval : entry.second){
            std::cout << "[";
            for(const auto& number : interval){
                std::cout << number << " ";
            }
            std::cout << "]";
        }
        std::cout << std::endl; 
    }
}


bool classOverlap(std::vector<std::vector<int>> stud1, std::vector<std::vector<int>> stud2){
    return false; 
}