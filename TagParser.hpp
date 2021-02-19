#ifndef PROJECT1PHASE1_TAGPARSER_HPP
#define PROJECT1PHASE1_TAGPARSER_HPP

#include <string>
#include <fstream>
#include "Token.hpp"
#include "TraversableStack.hpp"
#include "Tokenizer.hpp"
#include <vector>
#include <map>

class TagParser {

public:
    TagParser (std::string);
    void handleParse();

    // void handleToken(Tokenizer &tokenizer, Token token);
    //void handleToken(Token token);
    

    void handleOpenTag(Tokenizer &tokenizer, Token token);
    void handleCloseTag(Tokenizer &tokenizer, Token token);
    void printTheMap();
    bool findMatchingTagName(std::string);
    
    

    //void iterTagNames();
    //void printOut(std::string tagName);
    //void setNameTags(std::string );
    //bool tagExists(std::string);
    std::map<std::string, std::vector<Token> > tags; // creates an object

    
    

private:
    std::string inputFileName;  
    TraversableStack tStack;
    std::vector<Token> listOfTagNames;
    //std::vector<int> numOfOccur;
    //std::map<std::string, std::vector<Token> > tags;


    //Tokenizer &tokenizer;
    //Token &token; 
    

    
    
};

#endif //PROJECT1PHASE1_TAGPARSER_HPP