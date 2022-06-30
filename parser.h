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
	void isList(Token* tok);
	void error(string);
	void initSimbolTable();

	//Métodos da gramática (todos os não terminais)
	void program();  //line 1
	void classList();  //line 2
	void classDecl();  //line 3
	void classBody(); //line 4  -> fazer no .cpp
	void varDeclListOpt(); //line 5
	void varDeclList(); //line 6
	void varDeclListComma(); //line 6.1
	void varDecl(); //line 7
	void varDeclOpt(); //line 8
	void type(); //line 9
	void constructDeclListOpt(); //line 10
	void constructDeclList(); //line 11
	void constructDeclListComma(); //line 11.1
	void constructDecl(); //line 12
	void methodDeclListOpt(); //line 13
	void methodDeclList(); //line 14
	void methodDeclListComma(); //line 14.1
	void methodDecl(); //line 15
	void methodBody(); //line 16
	void paramListOpt(); //line 17
	void paramList(); //line 18
	void paramListComma(); //line 18.1
	void param(); //line 19
	void statementsOpt(); //line 20
	void statements(); //line 21
	void statementsComma(); //line 21.1
	void statement(); //line 22
	void atribStat(); //line 23
	void printStat(); //line 24
	void readStat(); //line 25
	void returnStat(); //line 26
	void superStat(); //line 27
	void ifStat(); //line 28
	void forStat(); //line 29
	void atribStatOpt(); //line 30
	void expressionOpt(); //line 31
	void lValue(); //line 32
	void lValueComp(); //line 33
	void expression(); //line 34
	void allocExpression(); //line 35
	void numExpression(); //line 36
	void term(); //line 37
	void unaryExpression(); //line 38
	void factor(); //line 39
	void argListOpt(); //line 40
	void argList(); //line 41
	void argListComma(); //line 41.1  

public:
	Parser(string);
	void run();
};
