//
// Created by Ali A. Kooshesh on 1/27/21.
//

#ifndef PROJECT1PHASE1_TOKENIZER_HPP
#define PROJECT1PHASE1_TOKENIZER_HPP

#include <string>
#include <fstream>
#include "Token.hpp"

class Tokenizer {

public:
    Tokenizer(std::string);
    Token getToken();

    bool getNextChar(char&); // helper 
    

private:
    int lineNumber, charPosition;
    std::string inputFileName;
    std::ifstream inputStream;

    bool charOfInterest(char c);
};

#endif //PROJECT1PHASE1_TOKENIZER_HPP
