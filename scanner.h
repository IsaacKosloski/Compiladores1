//#include "symboltable.h"
#include <fstream>
#include "token.h"

class Scanner
{
private:
    string input;//Armazena o texto de entrada
    int pos;//Posição atual
    int line;
    //SymbolTable* st;

public:
    //Construtor
    Scanner(string/*, SymbolTable*/);

    int getLine();

    //Método que retorna o próximo token da entrada
    Token* nextToken();

    //Método para manipular erros
    void lexicalError(string);

    //friend class Parser;
};
