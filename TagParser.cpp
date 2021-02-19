#include <iostream>
#include "TagParser.hpp"
#include "Tokenizer.hpp"

void TagParser::handleParse()
{

    //std::cout<<"I GOT CALLED" <<std::endl;
    Tokenizer tokenizer(inputFileName);

    Token token = tokenizer.getToken();
    while (!token.endOfFile()) {
        if( token.isOpenTag() ) // need tokenizer to determine whats after the open tag
            handleOpenTag(tokenizer, token); // you will have to write this and other similar functions
        else if( token.isCloseTag() )
            handleCloseTag(tokenizer, token);
        else if (token.isCloseStandAloneTag()){
            //same for correct input
            handleCloseTag(tokenizer, token);
        }
            
            
            
            
            
        else if(token.isCloseAngleBracket() || token.isOpenAngleBracket()) {
            token.reportRandomAngelBracket(token);
        } else {
            token.reportRandomToken(token);
        }
        token = tokenizer.getToken();
    }

}


TagParser::TagParser(std::string name): inputFileName{name}
{

    // Tokenizer tokenizer(inputFileName);

    // Token token = tokenizer.getToken();
    /*
    while (!token.endOfFile()) {
        if( token.isOpenTag() )
            handleOpenTag(tokenizer, token); // you will have to write this and other similar functions
        else if( token.isCloseTag() )
            handleCloseTag(tokenizer, token);
        else if(token.isCloseAngleBracket() || token.isOpenAngleBracket()) {
            token.print();
            std::cout << (token.isCloseAngleBracket() ? " ignoring random close angle-bracket."
                                                    : " ignoring random open angle-bracket.") << std::endl;
        } else {
            token.print();
            std::cout << " unknown token."  << std::endl;
        }
        token = tokenizer.getToken();
    }
    */
    
// tokens have finished, but you want to determine if
// there are open tags that have not been matched.

}

void TagParser::handleOpenTag(Tokenizer &tokenizer,Token token)
{

    //check to see if the next getToken() is a > if not report
    // token = tokenizer.getToken();

    // if (token.isCloseAngleBracket())
    //     tStack.push(token);
    // else
    // {
    //     /* code */
    // }
    tStack.push(token);

    //consume the > name different to keep char position
    token = tokenizer.getToken();
    if(token.isCloseStandAloneTag())
    {
        //push top of stack aka open tag -->map
        tags[tStack.top().tagName()].push_back(tStack.top());
        //push current aka close tag -->map
        tags[tStack.top().tagName()].push_back(token);
        tStack.pop();
    }

    else if (!token.isCloseAngleBracket())
    {
        //report ex on line 8 txt
        token.reportMissingAngleBracket(tStack.top());
        tStack.pop();

    }
    else if (token.isOpenTag())
        token = tokenizer.getToken();



    
}

bool TagParser::findMatchingTagName(std::string tagName){

    for(int i = 0; i < listOfTagNames.size(); i++){
        if( listOfTagNames[i].tagName() == tagName){
            return true;
        }
    }

    return false;

}

void TagParser::handleCloseTag(Tokenizer &tokenizer,Token token)
{
    //std::cout<<"I GOT CALLED" <<std::endl;

    //tags["p"].push_back(token);
    //std::cout << "The following is a list of well-informed HTML tags." << std::endl;

    if (!tStack.empty())
    {

        if (token.tagName() == tStack.top().tagName() )
        {
            //push top of stack aka open tag -->map
            tags[tStack.top().tagName()].push_back(tStack.top());
            //push current aka close tag -->map
            tags[tStack.top().tagName()].push_back(token);
            tStack.pop();
            //consume >
            token = tokenizer.getToken();

        }
        
        else
        {
            //report
            bool flag = false;

            while(!tStack.empty()){

                listOfTagNames.push_back(tStack.top());
                tStack.pop();
            }

            if(findMatchingTagName(token.tagName())){
                // iterate through and report which ones
                for(int i = 0; i < listOfTagNames.size(); i++)
                {
                    if(listOfTagNames[i].tagName() == token.tagName())
                        flag = true;

                    if(!flag)
                    {
                        //report
                        token.reportRemainOpen(listOfTagNames[i]);

                    }
                    


                }

                // restore stack
                for(int i = listOfTagNames.size() - 1; i > 0; i--)
                {
                    tStack.push(listOfTagNames[i]);

                }
        
            }
            

        }
    }
    else
    {
        Token token2 = tokenizer.getToken();
        token.reportClosingTag(token, token2);
    }






//     for(auto mapIter = tags.begin(); mapIter != tags.end(); ++mapIter) {
//     // our map, pairs an array of Tokens with tag-name strings.
//     std::cout << mapIter->first;
//     //tags[token.tagName()].push_back(token);
//     std::vector<Token> locations = mapIter->second;
//     for(std::vector<Token>::iterator vIter = locations.begin(); vIter != locations.end(); ++vIter) 
//     {
//         tags[token.tagName()].push_back(token);
//         vIter->print();
//         std::cout << std::endl;
        
//     }
// }
}

void TagParser::printTheMap(){
    
    std::cout << "\nThe following is a list of well-formed HTML tags." << std::endl;
    std::cout<<std::endl;
    for(auto mapIter = tags.begin(); mapIter != tags.end(); ++mapIter) 
    {
        // our map, pairs an array of Tokens with tag-name strings.
        std::vector<Token> locations = mapIter->second;

        std::cout << mapIter->first << " appeared in the following " << mapIter->second.size() / 2 << " locations" << std::endl;

        for(std::vector<Token>::iterator vIter = locations.begin(); vIter != locations.end(); ++vIter) 
        {
            if(vIter->isOpenTag())
                std::cout<<'\t';

            vIter->print(*vIter);
            
            if(vIter->isCloseStandAloneTag() || vIter->isCloseTag())
                std::cout << std::endl;
            else
                std::cout << " -- ";
            
        }
        std::cout<<std::endl;
    }
    
}




/*
void TagParser::handleToken(Token token)
{
    //tags[token.tagName()].push_back(token);
    
    if( token.isOpenTag() )
        handleOpenTag(token); // you will have to write this and other similar functions
        
    else if( token.isCloseTag() )
        handleCloseTag(token);
       /* 
    else if(token.isCloseAngleBracket() || token.isOpenAngleBracket()) {
        token.print();
        std::cout << (token.isCloseAngleBracket() ? " ignoring random close angle-bracket."
                                                    : " ignoring random open angle-bracket.") << std::endl;
    } else {
        token.print();
        std::cout << " unknown token."  << std::endl;
    }
    */

    
    //tStack.push(token);
/*
}
*/


/*
void TagParser::handleOpenTag(Token token)
{
        tStack.push(token);
    
}

*/

/*
void TagParser::handleCloseTag(Token token)
{


    for(auto mapIter = tags.begin(); mapIter != tags.end(); ++mapIter) {
    // our map, pairs an array of Tokens with tag-name strings.
    std::vector<Token> locations = mapIter->second;
    for(std::vector<Token>::iterator vIter = locations.begin(); vIter != locations.end(); ++vIter) 
    {
        vIter->print();
        std::cout << std::endl;
        /*
        if(vIter->tagName() == tagName)
        {
            vIter->print();
            std::cout << std::endl;
        }
        */
        /*
    }
}
}

*/


/*
}

/*
void TagParser::iterTagNames()
{
    std::cout << "The following is a list of well-infomred HTML tags." << std::endl;
    for(int i = 0; i < listOfTagNames.size(); i++ )
    {
        std::cout << listOfTagNames[i] << " appeared in the following " << numOfOccur[i] << " locations." << std::endl;
        printOut(listOfTagNames[i]);
    }

}
*/
/*
void TagParser::printOut(std::string tagName){

    

    for(auto mapIter = tags.begin(); mapIter != tags.end(); ++mapIter) {
    // our map, pairs an array of Tokens with tag-name strings.
    std::vector<Token> locations = mapIter->second;
    for(std::vector<Token>::iterator vIter = locations.begin(); vIter != locations.end(); ++vIter) 
    {
        vIter->print();
        std::cout << std::endl;
        /*
        if(vIter->tagName() == tagName)
        {
            vIter->print();
            std::cout << std::endl;
        }
        */
       /* 
    }
}
}

*/


/*
void TagParser::setNameTags(std::string tagName ){

    if(!tagExists(tagName))
    {
        listOfTagNames.push_back(tagName);
        numOfOccur.push_back(1);
    } else {

        for( int i = 0; i < listOfTagNames.size(); i++)
        {
            if(tagExists(tagName))
            {
                numOfOccur[i] = numOfOccur[i] + 1;
            }
        }
    
    }
}
*/



/*

bool TagParser::tagExists(std::string tagName)
{
    if(listOfTagNames.empty())
    {
        return false;
    }

    for (int i = 0; i < listOfTagNames.size(); i++)
    {
        if(listOfTagNames[i] == tagName)
        {
            return true;
        } 

    }
    return false;

}

*/

