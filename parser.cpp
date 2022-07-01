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
	t = new Token (EXTENDS);
	globalST->add(new STEntry(t,"extends", true));
	t = new Token (INT);
	globalST->add(new STEntry(t,"int", true));
	t = new Token (STRING);
	globalST->add(new STEntry(t,"string", true));
	t = new Token (BREAK);
	globalST->add(new STEntry(t,"break", true));
	t = new Token (PRINT);
	globalST->add(new STEntry(t,"print", true));
	t = new Token (READ);
	globalST->add(new STEntry(t,"read", true));
	t = new Token (RETURN);
	globalST->add(new STEntry(t,"return", true));
	t = new Token (SUPER);
	globalST->add(new STEntry(t,"super", true));
	t = new Token (IF);
	globalST->add(new STEntry(t,"if", true));
	t = new Token (ELSE);
	globalST->add(new STEntry(t,"else", true));
	t = new Token (FOR);
	globalST->add(new STEntry(t,"for", true));
	t = new Token (NEW);
	globalST->add(new STEntry(t,"new", true));
	t = new Token (CONSTRUCTOR);
	globalST->add(new STEntry(t,"constructor", true));
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
	varDeclListComma();
}

void
Parser::varDeclListComma()
{
	if (isType(lToken)) {
		varDecl();
		varDeclListComma();
	}
}

void
Parser::varDecl()
{
	type();
	isList(lToken);
	match(ID);
	varDeclListOpt();
	match(SEMICOLON);
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
		match(lToken->name);
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
	match(LEFT_BRACE);
	statementsOpt();
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
	paramListComma();
}
/*18.1. ParamListComma → , Param ParamListComma 
|epsolon*/
void
Parser::paramListComma()
{
	match(COMMA_LITERAL);
	param();
	paramListComma();
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
Parser::statementsOpt()
{
	if (isType(lToken)||
		lToken->name == PRINT||
		lToken->name == READ||
		lToken->name == RETURN||
		lToken->name == SUPER||
		lToken->name == IF||
		lToken->name == FOR||
		lToken->name == BREAK||
		lToken->name == SEMICOLON)
		statements();
}

//21. Statements → Statement StatementsComma 
void
Parser::statements()
{
	statement();
	statementsComma();
}

/*21.1. StatementsComma → Statement StatementsComma 
|epsolon*/
void
Parser::statementsComma()
{
	if (isType(lToken)||
		lToken->name == PRINT||
		lToken->name == READ||
		lToken->name == RETURN||
		lToken->name == SUPER||
		lToken->name == IF||
		lToken->name == FOR||
		lToken->name == BREAK||
		lToken->name == SEMICOLON)
	{
		statement();
		statementsComma();
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
Parser::statement()
{
	if(isType(lToken)){
		if (lToken->name == ID)
		{
			match(ID);
			if (lToken->name == LEFT_BRACKET) {
				match(LEFT_BRACKET);
				if (lToken->name == RIGHT_BRACKET) {
					match(RIGHT_BRACKET);
					match(ID);
					varDeclOpt();
					varDeclListComma();
				}
				else {
					atribStat();
					match(SEMICOLON);
				}
			}
			else if (lToken->name == ID) {
				match(ID);
				varDeclOpt();
				varDeclListComma();
			}
			else {
				atribStat();
				match(SEMICOLON);
			}
		}
		else
			varDeclList();
	}
	else if (lToken->name == PRINT) {
		match(PRINT);
		expression();
		match(SEMICOLON);
	}
	else if (lToken->name == READ) {
		match(READ);
		lValue();
		match(SEMICOLON);
	}
	else if (lToken->name == RETURN) {
		match(RETURN);
		expression();
		match(SEMICOLON);
	}
	else if (lToken->name == SUPER) {
		match(SUPER);
		match(LEFT_PARENTHESE);
		argListOpt();
		match(RIGHT_PARENTHESE);
		match(SEMICOLON);
	}
	else if (lToken->name == IF) {
		match(IF);
		match(LEFT_PARENTHESE);
		expression();
		match(RIGHT_PARENTHESE);
		match(LEFT_BRACE);
		statements();
		match(RIGHT_BRACE);
		if (lToken->name == ELSE) {
			match(ELSE);
			match(LEFT_BRACE);
			statements();
			match(RIGHT_BRACE);
		}
	}
	else if (lToken->name == FOR) {
		match(FOR);
		match(LEFT_PARENTHESE);
		atribStatOpt();
		match(SEMICOLON);
		expressionOpt();
		match(SEMICOLON);
		atribStatOpt();
		match(RIGHT_PARENTHESE);
		match(LEFT_BRACE);
		statements();
		match(RIGHT_BRACE);
	}
	else if (lToken->name == BREAK) {
		match(BREAK);
		match(SEMICOLON);
	}
	else if (lToken->name == SEMICOLON) {
		match(SEMICOLON);
	}
}
void
Parser::atribStat()
{
	if (lToken->name == ADDITION || lToken->name == SUBTRACTION) {
		expression();
		match(RIGHT_BRACKET);
	}
	lValueComp();
}

void
Parser::atribStatOpt() {
	if (lToken->name == ID) {
		match(ID);
		if (lToken->name == LEFT_BRACKET) {
			match(LEFT_BRACKET);
		}
		atribStat();
	}
}

/*31. ExpressionOpt → Expression
| epsolon*/
void
Parser::expressionOpt()
{
	if (lToken->name == ADDITION || lToken->name == SUBTRACTION) {
		expression();
	}
}
/*32. LValue → ID LValueComp
| ID [ Expression ] LValueComp*/
void
Parser::lValue() 
{
	match(ID);
	if (lToken->name == LEFT_BRACKET) {
		expression();
		match(RIGHT_BRACKET);
	}
	lValueComp();
}
/*33. LValueComp → . ID LValueComp
| . ID [ Expression ] LValueComp
| epsolon*/
void
Parser::lValueComp()
{
	match(DOT);
	match(ID);
	if (lToken->name == LEFT_BRACKET) {
		expression();
		match(RIGHT_BRACKET);
	}
	if(lToken->name == DOT)
		lValueComp();
}
/*34. Expression → NumExpression
| NumExpression RelOp NumExpression*/
void
Parser::expression() 
{
	numExpression();
	if (lToken->name == EQUAL || lToken->name == NOT_EQUAL ||
		lToken->name == LESS_OR_EQUAL || lToken->name == LESS_THAN ||
		lToken->name == GREATER_OR_EQUAL || lToken->name == GREATER_THAN)
	{
		match(lToken->name);
		numExpression();
	}
}
/*35. AllocExpression → new ID ( ArgListOpt )
| Type [ Expression ]*/
void
Parser::allocExpression() 
{
	if (lToken->name == NEW) {
		match(NEW);
		match(ID);
		match(LEFT_PARENTHESE);
		argListOpt();
		match(RIGHT_PARENTHESE);
	}
}

/*36. NumExpression → Term + Term
| Term - Term
| Term*/
void
Parser::numExpression()
{
	term();
	if (lToken->name == ADDITION)
	{
		match(ADDITION);
		term();
	}
	else if (lToken->name == SUBTRACTION)
	{
		match(SUBTRACTION);
		term();
	}
}

/*37. Term → UnaryExpression * UnaryExpression
| UnaryExpression / UnaryExpression
| UnaryExpression % UnaryExpression
| UnaryExpression
*/
void
Parser::term()
{
	unaryExpression(); 
	if (lToken->name == ASTERISK)
	{
		match(ASTERISK);
		unaryExpression();
	}
	else if (lToken->name == BAR)
	{
		match(BAR);
		unaryExpression();
	}
	else if (lToken->name == MODULAR)
	{
		match(MODULAR);
		unaryExpression();
	}
}

/*38. UnaryExpression → + Factor
| - Factor*/
void
Parser::unaryExpression()
{
	if (lToken->name == ADDITION)
		match(ADDITION);
	else
		match(SUBTRACTION);
	factor();
}

/*39. Factor → INTEGER_LITERAL
| STRING_LITERAL
| LValue
| ( Expression )*/
void
Parser::factor()
{
	if (lToken->name == INTEGER_LITERAL)
		match(INTEGER_LITERAL);
	else if (lToken->name == STRING_LITERAL)
		match(STRING_LITERAL);
	else if (lToken->name == ID)
			lValue();
	else if (lToken->name == LEFT_PARENTHESE)
	{
		match(LEFT_PARENTHESE);
		expression();
		match(RIGHT_PARENTHESE);
	}
}

/*40. ArgListOpt → ArgList
| epsolon*/
void
Parser::argListOpt()
{
	if (lToken->name == ADDITION || lToken->name == SUBTRACTION)
		argList();
}

/*41. ArgList → Expression ArgListComma*/
void
Parser::argList()
{
	expression();
	argListComma();
}

/*41.1.ArgListComma → , Expression ArgListComma
|epsolon*/
void
Parser::argListComma()
{
	if (lToken->name == COMMA_LITERAL)
	{
		match(COMMA_LITERAL);
		expression();
		argListComma();
	}
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
