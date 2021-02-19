#include <iostream>
#include <fstream>
#include "Tokenizer.hpp"
#include "TagParser.hpp"



int main(int argc, char *argv[]) {

    if( argc != 2 ) {  // we expect the name of the file as an argument to the program.
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile" << std::endl;
        exit(1);
    }

    // Here, we open the file to make sure that it exists before starting the program.
    // When using CLion, the input file has to be in cmake-build-debug directory.
    std::ifstream inputStream;
    std::ofstream oFile;
    std::string ending = argv[1];
    std::string fileName_out = "output_" + ending;
    oFile.open(fileName_out);

    if (!oFile.is_open())
    {
        std::cout << "Couldn't open file" << argv[1] << std::endl;
        exit(1);
    }
    inputStream.open(argv[1], std::ios::in);    // open for reading
    if( ! inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        std::cout << strerror(errno) << std::endl;
        exit(2);
    }

 
    inputStream.close();




    Tokenizer tokenizer(argv[1]);
    TagParser tagParser(argv[1]);
    tagParser.handleParse();
    // Token token = tokenizer.getToken();  // get the first token to start the while loop
    
    //TraversableStack tStack;
    //tStack.push(token);

    //MAP
    
    //tagParser.tags[token.tagName()].push_back(token);

    
  

    // while( ! token.endOfFile() )
    //  {
    //     // token.print();
    //     // token.writeToFile(oFile);
    //     // token = tokenizer.getToken();
    //     // tagParser.handleParse();
    //     //tagParser.handleToken(token);

    //    // tStack.push(token);

    //    //MAP
        
    //     //tagParser.tags[token.tagName()].push_back(token);
    //     //tagParser.setNameTags(token.tagName());
    // }

    

    oFile.close();



    //tStack.empty();

    // dubug purposes
    //std::cout << "This is my Stack: " << std::endl;
    //tagParser.printStack();
    //std::cout << std::endl;

    // std::cout<< "TESTING MAP" << std::endl;
    // for(auto mapIter = tagParser.tags.begin(); mapIter != tagParser.tags.end(); ++mapIter) {
    // // our map, pairs an array of Tokens with tag-name strings.
    // std::vector<Token> locations = mapIter->second;
    // for(std::vector<Token>::iterator vIter = locations.begin(); 
    //                                  vIter != locations.end(); ++vIter) {
    //   vIter->print();
    //   std::cout << std::endl;
    // }
  //}
     //tagParser.iterTagNames();

    tagParser.printTheMap();


    return 0;
}
