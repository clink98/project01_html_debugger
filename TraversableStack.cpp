#include <iostream>
#include "TraversableStack.hpp"

void TraversableStack::push(Token token)
{
    TraversableStack.push_back(token);
}

Token TraversableStack::top()
{
    return TraversableStack.at(TraversableStack.size() - 1);
}

void TraversableStack::pop()
{
    TraversableStack.pop_back();
}

bool TraversableStack::empty()
{
    return TraversableStack.empty();
}

void TraversableStack::clear() {
    while(!TraversableStack.empty()){
        TraversableStack.pop_back();
    }
}