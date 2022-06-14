#include "scanner.h"

class Parser
{
private:
	Scanner* scanner;
	Token* lToken;
	SymbolTable* globalST;
	SymbolTable* currentST;

	void advance();
	void match(int);
	bool isType(Token*);
	void error(string);
	void initSimbolTable();

	void program();
	void classList();
	void classDecl();
	//Continuar

public:
	Parser(string);
	void run();
};
