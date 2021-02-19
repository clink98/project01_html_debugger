//
// Created by Ali A. Kooshesh on 1/27/21.
//

#include <iostream>
#include <iomanip>
#include "Token.hpp"

Token::Token(int line, int pos): _isOpenTag{false},
                                 _isCloseTag{false},
                                 _isCloseAngleBracket{false},
                                 _isCloseStandAloneTag{false},
                                 _tagName{""},
                                 _eof{false},
                                 _lineNumber{line},
                                 _charPos{pos} {}

bool &Token::isOpenTag() { return _isOpenTag; }
bool &Token::isCloseTag() { return _isCloseTag; }

bool &Token::isCloseAngleBracket() { return _isCloseAngleBracket; }
bool &Token::isOpenAngleBracket() { return _isOpenAngleBracket; }

bool &Token::endOfFile() { return _eof; }
bool &Token::eol() {
    return _eol; // sets value of eol to true or false and also to tell us if it is true or false (both)
}
bool &Token::isCloseStandAloneTag() { return _isCloseStandAloneTag; }

std::string Token::tagName() { return _tagName; }

void Token::makeOpenTag(std::string name) {
    _tagName = name;
    isOpenTag() = true;
}

void Token::makeCloseTag(std::string name) {
    _tagName = name;
    isCloseTag() = true;
}


void Token::print(Token vIter) {

    if(vIter.isCloseStandAloneTag())
        std::cout << "[" << std::setw(2) << _lineNumber << ", " <<  std::setw(3) << _charPos << "] " << " " << "/>";
    else
        std::cout << "[" << std::setw(2) << _lineNumber << ", " <<  std::setw(3) << _charPos << "] " << " " << "</" << tagName();



     //std::cout << "The following is a list of well-informed HTML tags." << std::endl;
    //  if(isOpenTag()){
    //     std::cout << tagName() << " appeared in the following locations." << std::endl;
    //  }
    // std::cout << "[" << std::setw(2) << _lineNumber << ", " <<  std::setw(3) << _charPos << "] " << std::endl;
    


    /*

    std::cout << "[" << std::setw(2) << _lineNumber << ", " <<  std::setw(3) << _charPos << "] ";



    if(isOpenTag()) {

        std::cout << "<" << tagName() << std::endl;
    } else if(isCloseStandAloneTag()) {
       // std::cout << "[" << _lineNumber << ", " << _charPos << "] ";
        std::cout << "/>" <<std::endl;
        
    } else if(isCloseTag()){
        std::cout << "</" << tagName() << std::endl;
        
    
    } else if (isCloseAngleBracket()){
        std::cout << ">" << std::endl;
    } 
    else {  // more else if's before this else

    }

    */
}

void Token::print2() {

    std::cout << "[" << std::setw(2) << _lineNumber << ", " <<  std::setw(3) << _charPos << "] ";



    if(isOpenTag()) {

        std::cout << "<" << tagName() << std::endl;
    } else if(isCloseStandAloneTag()) {
       // std::cout << "[" << _lineNumber << ", " << _charPos << "] ";
        std::cout << "/>" <<std::endl;
        
    } else if(isCloseTag()){
        std::cout << "</" << tagName() << std::endl;
        
    
    } else if (isCloseAngleBracket()){
        std::cout << ">" << std::endl;
    } 
    else {  // more else if's before this else

    }
}

void Token::upDateCharPos(int newPos){

    _charPos = newPos;
}

void Token::writeToFile(std::ofstream& oFile)
{
    
       oFile  << "[" << std::setw(2) << _lineNumber << ", " <<  std::setw(3) << _charPos << "] ";

    if(isOpenTag()) {
        oFile  << "<" << tagName() << std::endl;
    } else if(isCloseStandAloneTag()) {
       // std::cout << "[" << _lineNumber << ", " << _charPos << "] ";
        oFile  << "/>" <<std::endl;
        
    } else if(isCloseTag()){
        oFile  << "</" << tagName() << std::endl;
        
    
    } else if (isCloseAngleBracket()){
        oFile  << ">" << std::endl;
    } 
    else {  // more else if's before this else

    }

}

void Token::reportClosingTag(Token token, Token token2){
    
    std::cout<< "[" << std::setw(2) << token._lineNumber << ", " <<  std::setw(3) << token._charPos << "] " 
    << "</" << token.tagName() << " (with close angle bracket " << "[" << std::setw(2) << token2._lineNumber << ", " <<  std::setw(3) << token2._charPos << "] >) " << "doesn't have a matching open tag. Will discard it."<<std::endl;
}

void Token::reportMissingAngleBracket(Token token){

    std::cout << "[" << std::setw(2) << token._lineNumber << ", " <<  std::setw(3) << token._charPos << "] "
    << "<" << token.tagName() << " is missing a '>' or '/>'. Will discard it." << std::endl;
}

void Token::reportRandomAngelBracket(Token token){

    std::cout << "[" << std::setw(2) << token._lineNumber << ", " <<  std::setw(3) << token._charPos << "] ";

    if (token.isOpenAngleBracket()){
        std::cout<< "< ignoring random open angle-bracket." << std::endl;
    }
    else{
        std::cout<< "> ignoring random close angle-bracket." << std::endl;
    }


    // std::cout << (token.isCloseAngleBracket() ? " ignoring random close angle-bracket."
    // : " ignoring random open angle-bracket.") << std::endl;
}

void Token::reportRandomToken(Token token){
    std::cout << "Unkown Token " << "[" << std::setw(2) << token._lineNumber << ", " <<  std::setw(3) << token._charPos << "] " << token.tagName() << std::endl;

}

void Token::reportRemainOpen(Token token ){

    std::cout << "[" << std::setw(2) << token._lineNumber << ", " <<  std::setw(3) << token._charPos << "] "
    << " <" << token.tagName() << std::endl;
}