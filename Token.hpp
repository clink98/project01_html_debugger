//
// Created by Ali A. Kooshesh on 1/27/21.
//

#ifndef PROJECT1PHASE1_TOKEN_HPP
#define PROJECT1PHASE1_TOKEN_HPP

#include <string>
#include <fstream>


class Token {
public:
    Token(int, int);
    bool &isOpenTag();
    bool &isCloseTag();

    bool &isCloseAngleBracket();
    bool &isOpenAngleBracket();

    bool &endOfFile();
    bool &eol();
    bool &isCloseStandAloneTag();

    std::string tagName();

    void makeOpenTag(std::string);
    void makeCloseTag(std::string);
    void upDateCharPos(int);
    void print(Token);
    void print2();
    void writeToFile(std::ofstream& oFile);
    void reportClosingTag(Token,Token);
    void reportMissingAngleBracket(Token);
    void reportRandomAngelBracket(Token);
    void reportRandomToken(Token);
    void reportRemainOpen(Token);

    

private:
    bool _isOpenTag, _isCloseTag, _isCloseAngleBracket,
            _isOpenAngleBracket,_eof,_eol, _isCloseStandAloneTag;

    std::string _tagName;
    int _lineNumber, _charPos;
};



#endif //PROJECT1PHASE1_TOKEN_HPP
