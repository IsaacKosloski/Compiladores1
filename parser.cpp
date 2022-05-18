#include "parser.h"

//Construtor que recebe o nome do arquivo de entrada
//como argumento
Parser::Parser(string input)
{
	//currentST = globalST = new SymbolTable();
	//initSimbolTable();

	scanner = new Scanner(input);
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

Parser::classBody()
{
	match((SEP, LEFT_BRACE));
	varDeclListOpt();
	constructDeclListOpt();
	methodDeclListOpt();
	match((SEP, RIGHT_BRACE));
}
//Parser::varDeclListOpt()
//{
//	varDeclList();
//}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
