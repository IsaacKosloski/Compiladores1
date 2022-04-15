#include "scanner.h"    

//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input/*, SymbolTable* table*/)
{
    this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;
    pos = 0;
    line = 1;

    //A próxima linha deve ser comentada posteriormente.
    //Ela é utilizada apenas para verificar se o 
    //preenchimento de input foi feito corretamente.
    cout << this->input;

}

int Scanner::getLine()
{
    return line;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* tok;
    //string lexeme;
    int state = 1;

    while (true)
    {
        switch(state)
        {
            case 1:
                if (input[pos] == '<')
                {
                    pos++;
                    state = 2;
                }
                else if (input[pos] == '=')
                {
                    pos++;
                    state = 5;
                }
                else if (input[pos] == '>')
                {
                    pos++;
                    state = 8;
                }
                else if (input[pos] == '!')
                {
                    pos++; 
                    state = 11;
                }
                else if (input[pos] == '+')
                {
                    pos++;
                    state = 13;
                }
                else if(input[pos] == '-')
                {
                    pos++;
                    state = 14;
                }
                else if(input[pos] == '*')
                {
                    pos++;
                    state = 15;
                }
                else if(input[pos] == '/')
                {
                    pos++;
                    state = 16;
                }
                else if(input[pos] == '%')
                {
                    pos++;
                    state = 17;
                }
                break;
            case 2:
                if (input[pos] == '='){
                    pos++;
                    state = 3;
                }
                else{
                    pos++;
                    state = 4;
                }
                break;
            case 5:
                if (input[pos] == '='){
                    pos++;
                    state = 6;
                }
                else{
                    pos++;
                    state = 7;
                }
                break;
            case 8:
                if (input[pos] == '='){
                    pos++;
                    state = 9;
                }
                else{
                    pos++;
                    state = 10;
                }
            case 11:
                if (input[pos] == '='){
                    pos++;
                    state = 12;
                }
        }    
    }
    return tok;
}
void Scanner::lexicalError(string msg)
{
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}