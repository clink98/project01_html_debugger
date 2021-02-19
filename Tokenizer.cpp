//
// Created by Ali A. Kooshesh on 1/27/21.
//

#include <iostream>
#include "Tokenizer.hpp"


Tokenizer::Tokenizer(std::string name): lineNumber{1},
                                        charPosition{1},
                                        inputFileName{name} {
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

bool Tokenizer::charOfInterest(char c) {
    // is c the initial (or the sole) character of a token?
    //char of interest <,>,/
    
    return c == '<' || c == '>' || c == '/'  ;   // you need to replace this with code that compares c with characters like '<', '>', etc.
}

bool Tokenizer::getNextChar(char& c){

    inputStream.get(c);
    charPosition++; 

    if( inputStream.eof() )
    {   
        return false;
            
    } 
    return true;
    
    
    
}

Token Tokenizer::getToken() {
    char c;
    
    

    if( ! inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }

    
    while( getNextChar(c) && ! charOfInterest(c) ) { //READING NULL WHEN NEW LINE GETS HIT
        // keep track of the line number and the character position here.
        if(c =='\n')
        {
            lineNumber++;
        } 
       
        
        
        if(c == '"')
        {
            
            getNextChar(c);

            while(c != '"')
            {
                
                getNextChar(c);

                if(c =='\n')
                {
                    lineNumber++;
                } 

            }
        }

    }


 
    Token token(lineNumber, charPosition-1);
    if( inputStream.eof() )
    {   
        token.endOfFile() = true;
    }


        //purpose-->get tagName
        // Immediately after an open angle-bracket, we will have to see
        // the tag name. That is, at this point, inputStream.peek() should
        // be a letter. If it is, then read the tag name, create an
        // open tag token for it. If inputStream.peek() is not a letter,
        // you will return a token that represents "random" open angle-bracket.

        // Let's assume that there was a tag name after the < and that it contained
        // em. Here is how we create a token for it.

    if(c == '<')
    {
        // charPosition++; // ?????
        
        if(inputStream.peek() == '/')
        {
            
            getNextChar(c);
           

            std::string tagNameTemp;
            while(!charOfInterest(inputStream.peek()))
            {
                
                getNextChar(c);
                tagNameTemp += c;

             } 
            
            token.makeCloseTag(tagNameTemp);
            
        } 
        else if(isalpha(inputStream.peek()))
        { 
            
            getNextChar(c);
            std::string tName(1,c);       
          
            while(!charOfInterest(inputStream.peek()) && inputStream.peek() != ' ')
            {
           

                getNextChar(c);
                tName += c;
                
                
            }
            
            token.makeOpenTag(tName);
            
        }
    }

    else if(c == '/')
    {
        
       getNextChar(c);

        token.isCloseStandAloneTag() = true;
       

    }

      else if( c == '>' )
    {
      
        token.isCloseAngleBracket() = true;
        
    }


    return token;

}


