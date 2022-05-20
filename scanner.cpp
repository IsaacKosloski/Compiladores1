#include "scanner.h"  
#include "ctype.h"


//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input/*, SymbolTable* table*/)
{
    /*this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;*/
    pos = 0;
    line = 1;

    //st = table;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        //ignora espaço em branco
        while (getline(inputFile,line) )
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 

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
        while (isspace(input[pos]))
            pos++;
        switch (state)
        {
        case 1:
            //Op < ou <=
            if (input[pos] == '<')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, LESS_OR_EQUAL);
                }
                else {
                    tok = new Token(OP, LESS_THAN);
                }
            }
            //Op = ou ==
            else if (input[pos] == '=')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, EQUAL);
                }
                else {
                    tok = new Token(OP, ASSIGNMENT);
                }
            }
            //Op >= ou >
            else if (input[pos] == '>')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, GREATER_OR_EQUAL);
                }
                else {
                    tok = new Token(OP, GREATER_THAN);
                }
            }
            // Op que ! seguido de =,
            // se o ! não for seguido de =
            // ocorreu um erro léxico
            else if (input[pos] == '!')
            {
                pos++;
                if (input[pos] == '=') {
                    pos++;
                    tok = new Token(OP, NOT_EQUAL);
                }
                else {
                    lexicalError("Expected = after !");
                }
            }
            //Op +
            else if (input[pos] == '+')
            {
                pos++;
                tok = new Token(OP, ADDITION);
            }
            //Op -
            else if (input[pos] == '-')
            {
                pos++;
                tok = new Token(OP, SUBTRACTION);
            }
            //Op *
            else if (input[pos] == '*')
            {
                pos++;
                tok = new Token(OP, ASTERISK);
            }
            //Op / ou comentário
            else if (input[pos] == '/')
            {
                pos++;
                // comentário de linha
                if (input[pos] == '/') {
                    while (input[pos] != '\n')
                        pos++;
                    state = 1;
                    //ignora o comentário
                    //procura o próximo token
                }
                // comentário de bloco
                else if (input[pos] == '*') {
                    state = 2;
                }
                // Op /
                else {
                    tok = new Token(OP, BAR);
                }
            }
            // Op %
            else if (input[pos] == '%')
            {
                pos++;
                tok = new Token(OP, MODULAR);
            }
            // Sep ;
            else if (input[pos] == ';') {
                pos++;
                tok = new Token(SEP, SEMICOLON);
            }
            // Sep (
            else if (input[pos] == '(') {
                pos++;
                tok = new Token(SEP, LEFT_PARENTHESE);
            }
            // Sep )
            else if (input[pos] == ')') {
                pos++;
                tok = new Token(SEP, RIGHT_PARENTHESE);
            }
            // Sep {
            else if (input[pos] == '{') {
                pos++;
                tok = new Token(SEP, LEFT_BRACE);
            }
            // Sep }
            else if (input[pos] == '}') {
                pos++;
                tok = new Token(SEP, RIGHT_BRACE);
            }
            // Sep ]
            else if (input[pos] == ']') {
                pos++;
                tok = new Token(SEP, RIGHT_BRACE);
            }
            // Sep [
            else if (input[pos] == '[') {
                pos++;
                tok = new Token(SEP, LEFT_BRACKET);
            }
            // Sep ,
            else if (input[pos] == ',') {
                pos++;
                tok = new Token(SEP, COMMA_LITERAL);
            }
            // Sep :
            else if (input[pos] == ':') {
                pos++;
                tok = new Token(SEP, COLON);
            }
            // Sep .
            else if (input[pos] == '.') {
                pos++;
                tok = new Token(SEP, DOT);
            }
            // Número inteiro
            else if (isdigit(input[pos])) {
                pos++;
                while (isdigit(input[pos]))
                    pos++;
                tok = new Token(INTEGER_LITERAL);
            }
            // ID
            else if (isalpha(input[pos]) || input[pos] == '_') {
                pos++;
                while (isalpha(input[pos]) || isdigit(input[pos]) || input[pos] == '_')
                    pos++;
                tok = new Token(ID);
            }
            //String
            else if (input[pos] == '"') {
                pos++;
                while(input[pos++] != '"')
                    pos++;
                tok = new Token(STRING_LITERAL);
            }
            //final de arquivo
            else if (input[pos] == '\0')
                tok = new Token(END_OF_FILE);
            return tok;
        case 2:
            // Comentário /* qualquer coisa até encontrar *
            while (input[pos] != '*')
                pos++;
            //ao encontrar * vai para o estado 3
            state = 3;
        case 3:
            //se encontrar / encerra o comentário
            if (input[pos] == '/') {
                pos++;
                // vai para o estado um para encontrar o token
                state = 1;
            }
            else //se não encontrar / volta a procurar *
                state = 2;
        }
    }
}
    void Scanner::lexicalError(string msg)
    {
        cout << "Linha " << line << ": " << msg << endl;

        exit(EXIT_FAILURE);
    }
