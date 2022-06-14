#include "stentry.h"

STEntry::STEntry()
{}
        
STEntry::STEntry(Token* tok, string lex)
{
    token = tok;
    lexeme = lex;
    reserved = false;
    
    //double var = 2.e+24;
}

STEntry::STEntry(Token* tok, string lex, bool res)
{
    token = tok;
    lexeme = lex;
    reserved = res;
}