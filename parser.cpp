#include "parser.h"

//Construtor que recebe o nome do arquivo de entrada
//como argumento
Parser::Parser(string input)
{
	currentST = globalST = new SymbolTable();
	initSimbolTable();

	scanner = new Scanner(input, currentST);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
}

bool
Parser::isType(Token* tok)
{
	if (tok->name == INTEGER_LITERAL || tok->name == STRING_LITERAL || tok->name == ID)
		return true;

	return false;
}

void
Parser::run()
{
	advance();

	program();

	cout << "Compilação encerrada com sucesso!\n";
}

void
Parser::initSimbolTable() {

	Token* t;

	t = new Token(CLASS);
	globalST->add(new STEntry(t, "class", true));
	t = new Token(EXTENDS);
	globalST->add(new STEntry(t,"extends",true));
	t = new Token(INT);
	globalST->add(new STEntry(t,"int",true));
	t = new Token(STRING);
	globalST->add(new STEntry(t,"string",true));
	t = new Token(BREAK);
	globalST->add(new STEntry(t,"break",true));
	t = new Token(PRINT);
	globalST->add(new STEntry(t,"print",true));
	t = new Token(READ);
	globalST->add(new STEntry(t,"read",true));
	t = new Token(RETURN);
	globalST->add(new STEntry(t,"return",true));
	t = new Token(IF);
	globalST->add(new STEntry(t,"if",true));
	t = new Token(ELSE);
	globalST->add(new STEntry(t,"else",true));
	t = new Token(FOR);
	globalST->add(new STEntry(t,"for",true));
	t = new Token(NEW);
	globalST->add(new STEntry(t,"new",true));
	t = new Token(CONSTRUCTOR);
	globalST->add(new STEntry(t,"constructor",true));

}

void
Parser::program()
{
	if (lToken->name == CLASS)
		classList();
}

void
Parser::classList()
{
	do
	{
		classDecl();
	} while (lToken->name == CLASS);
}

void
Parser::classDecl()
{
	match(CLASS);
	match(ID);

	if (lToken->name == EXTENDS)
	{
		advance();
		match(ID);
	}

	classBody();
}



void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
