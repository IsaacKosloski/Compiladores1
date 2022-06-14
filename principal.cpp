#include "parser.h"

int main(int argc, char* argv[]) 
{    
    Parser* parser = new Parser(argv[1]);

    parser->run();

    delete parser;
    
    return 0;
}