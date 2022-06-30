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

//Função para verificar se é uma lista, dadas as produções em: 7, 15 e 19
void
Parser::isList(Token* tok)
{
	if (tok->name == LEFT_BRACKET)
	{
		match(LEFT_BRACKET);
		match(RIGHT_BRACKET);
	}
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
Parser::classBody()
{
	match(LEFT_BRACE);
	varDeclListOpt();
	constructDeclListOpt();
	methodDeclListOpt();
	match(RIGHT_BRACE);
}

void 
Parser::varDeclListOpt()
{
	if (isType(lToken))
	{
		varDeclList();
	}
}

void
Parser::varDeclList()
{
	varDecl();
	varDeclComma();
}

void
Parser::varDeclComma();
{
	if (isType(lToken))
		varDecl();
	
}

void
Parser::varDecl()
{
	type();
	isList(lToken);
	match(ID);
	varDeclListOpt();
}

void
Parser::varDeclOpt()
{
	if (lToken->name == COMMA_LITERAL)
	{
		match(COMMA_LITERAL);
		match(ID);
		varDeclOpt();
	}
}

void
Parser::type()
{
	if (isType(lToken))
		match(lToken->name)
}

/*10. ConstructDeclListOpt → ConstructDeclList
| epsolon*/
void
Parser::constructDeclListOpt()
{
	if (lToken->name == CONSTRUCTOR)
		constructDeclList();
}

//11. ConstructDeclList → ConstructDecl ConstructDeclListComma
void
Parser::constructDeclList()
{
	constructDecl();
	constructDeclListComma();
}

/*11.1. ConstructDeclListComma → ConstructDecl ConstructDeclListComma
|epsolon
*/
void
Parser::constructDeclListComma()
{
	if (lToken->name == CONSTRUCTOR)
	{
		constructDecl();
		constructDeclListComma();
	}	
}

//12. ConstructDecl → constructor MethodBody
void
Parser::constructDecl()
{
	match(CONSTRUCTOR);
	methodBody();
}
/*13. MethodDeclListOpt → MethodDeclList
| epsolon*/
void
Parser::methodDeclListOpt()
{
	if (isType(lToken))
		methodDeclList();
}

//14. MethodDeclList → MethodDecl MethodDeclListComma
void
Parser::methodDeclList()
{
	methodDecl();
	methodDeclListComma();
}

/*14.1 MethodDeclListComma → MethodDecl MethodDeclListComma
|epsolon*/
void
Parser::methodDeclListComma()
{
	if (isType(lToken))
	{
		methodDecl();
		methodDeclListComma();
	}
}

/*15. MethodDecl → Type ID MethodBody
| Type [] id MethodBody*/
void
Parser::methodDecl()
{
	type();
	isList(lToken);
	match(ID);
	methodBody();
}

//16. MethodBody → ( ParamListOpt ) { StatementsOpt }
void
Parser::methodBody()
{
	match(LEFT_PARENTHESE);
	paramListOpt();
	match(RIGHT_PARENTHESE);
	match(LEFT_BRACE)
	statmentsOpt();
	match(RIGHT_BRACE);
}

/*17. ParamListOpt → ParamList
| epsolon*/
void
Parser::paramListOpt()
{
	if(isType(lToken))
		paramList();
}

//18. ParamList → Param ParamListComma 
void
Parser::paramList()
{
	param();
	paramlistComma();
}
/*18.1. ParamListComma → , Param ParamListComma 
|epsolon*/
void
Parser::paramlistComma()
{
	match(COMMA_LITERAL);
	param();
	paramlistComma();
}

/*19. Param → Type ID
| Type [] ID*/
void
Parser::param()
{
	type();
	isList(lToken);
	match(ID);
}

/*StatementsOpt → Statements
| epsolon*/
void
Parser::statmentsOpt()
{
	if (isType(lToken)||
		lToken == PRINT||
		lToken == READ||
		lToken == RETURN||
		lToken == SUPER||
		lToken == IF||
		lToken == FOR||
		lToken == BREAK||
		lToken == SEMICOLON)
		statments();
}

//21. Statements → Statement StatementsComma 
void
Parser::statments()
{
	statment();
	statmentsComma();
}

/*21.1. StatementsComma → Statement StatementsComma 
|epsolon*/
void
Parser::statmentsComma()
{
	if (isType(lToken)||
		lToken == PRINT||
		lToken == READ||
		lToken == RETURN||
		lToken == SUPER||
		lToken == IF||
		lToken == FOR||
		lToken == BREAK||
		lToken == SEMICOLON)
	{
		statment();
		statmentsComma();
	}
}

/*22. Statement → VarDeclList
| AtribStat ;
| PrintStat ;
| ReadStat ;
| ReturnStat ;
| SuperStat ;
| IfStat
| ForStat
| break ;
| ;*/
void
Parser::statment()
{
	if (lToken == ID)
	{
		Token* lTokenReserv = lToken;
		match(ID);
		if (lToken == ID)
			lToken = lToken-> ;
	}

	switch(lToken)
	{
		case ():
			varDeclList();
			break;
		case 
	}
}




void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}