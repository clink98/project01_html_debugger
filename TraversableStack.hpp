#ifndef PROJECT1PHASE1_TRAVERSABLESTACK_HPP
#define PROJECT1PHASE1_TRAVERSABLESTACK_HPP

#include <string>
#include <fstream>
#include "Token.hpp"
#include <vector>

class TraversableStack {

public:
    void push(Token token);
    Token top();
    void pop();
    bool empty();

    void clear(); 
    

private:

    std::vector<Token> TraversableStack;
    
};

#endif //PROJECT1PHASE1_TRAVERSABLESTACK_HPP