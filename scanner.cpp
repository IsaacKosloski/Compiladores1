#include "scanner.h"  
#include "ctype.h"


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
        while (input[pos] == ' ')
            pos++;
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
                    state = 3;
                }
                else if (input[pos] == '>')
                {
                    pos++;
                    state = 4;
                }
                else if (input[pos] == '!')
                {
                    pos++; 
                    state = 5;
                }
                else if (input[pos] == '+')
                {
                    pos++;
                    tok = new Token(OP, ADDITION);
                    return tok;
                }
                else if(input[pos] == '-')
                {
                    pos++;
                    tok = new Token(OP, SUBTRACTION);
                    return tok;
                }
                else if(input[pos] == '*')
                {
                    pos++;
                    tok = new Token(OP, ASTERISK);
                    return tok;
                }
                else if(input[pos] == '/')
                {
                    pos++;
                    tok = new Token(OP, BAR);
                    return tok;
                }
                else if(input[pos] == '%')
                {
                    pos++;
                    tok = new Token(OP, MODULAR);
                    return tok;
                }
                else if (input[pos] == ';') {
                    pos++;
                    tok = new Token(SEP, SEMICOLON);
                    return tok;
                }
                else if (input[pos] == '(') {
                    pos++;
                    tok = new Token(SEP, LEFT_PARENTHESE);
                    return tok;
                }
                else if (input[pos] == ')') {
                    pos++;
                    tok = new Token(SEP, RIGHT_PARENTHESE);
                    return tok;
                }
                else if (input[pos] == '{') {
                    pos++;
                    tok = new Token(SEP, LEFT_BRACE);
                    return tok;
                }
                else if (input[pos] == '}') {
                    pos++;
                    tok = new Token(SEP, RIGHT_BRACE);
                    return tok;
                }
                else if (input[pos] == ']') {
                    pos++;
                    tok = new Token(SEP, RIGHT_BRACE);
                    return tok;
                }
                else if (input[pos] == '[') {
                    pos++;
                    tok = new Token(SEP, LEFT_BRACKET);
                    return tok;
                }
                else if (input[pos] == ',') {
                    pos++;
                    tok = new Token(SEP, COMMA_LITERAL);
                    return tok;
                }
                else if (input[pos] == ':') {
                    pos++;
                    tok = new Token(SEP, COLON);
                    return tok;
                }
                else if (input[pos] == '.') {
                    pos++;
                    tok = new Token(SEP, DOT);
                    return tok;
                }
                else if (isdigit(input[pos])) {
                    pos++;
                    state = 6;
                }
                break;

            case 2:
                if (input[pos] == '='){
                    pos++;
                    tok = new Token(OP, LESS_OR_EQUAL);
                    return tok;
                }
                else{
                    tok = new Token(OP, LESS_THAN);
                    return tok;
                }
                break;

            case 3:
                if (input[pos] == '='){
                    pos++;
                    tok = new Token(OP, EQUAL);
                    return tok;
                }
                else{
                    tok = new Token(OP, ASSIGNMENT);
                    return tok;
                }
                break;
            case 4:
                if (input[pos] == '='){
                    pos++;
                    tok = new Token(OP, GREATER_OR_EQUAL);
                    return tok;
                }
                else{
                    tok = new Token(OP, GREATER_THAN);
                    return tok;
                }
                break;
            case 5:
                if (input[pos] == '='){
                    pos++;
                    tok = new Token(OP, NOT_EQUAL);
                    return tok;
                }
                break;
            case 6:
                while (isdigit(input[pos]))
                    pos++;
                tok = new Token(INTEGER_LITERAL);
                return tok;
                break;
        }    
    }
}
void Scanner::lexicalError(string msg)
{
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}