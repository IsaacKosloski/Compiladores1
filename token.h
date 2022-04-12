#include<iostream>
#include<ctype.h>
#include<string.h>

using namespace std;

enum Names { UNDEFINED, ID, INTEGER_LITERAL, OP, LESS_THAN, GREATER_THAN, LESS_OR_IQUAL, GREATER_OR_EQUAL, ADDITION, SUBTRACTION, ASTERISK, BAR, MODULE, ASSIGNMENT, EQUAL, NOT_EQUAL, SEP, LEFT_PARENTHESE, RIGHT_PARENTHESE, LEFT_BRACKET, RIGHT_BRACKET, LEFT_BRACE, RIGHT_BRACE, SEMICOLON, DOT, COMMA  LITERAL, LEFT_INVERTED_COMMAS, RIGHT_INVERTED_COMMAS, END_OF_FILE};


class Token
{
	public:
		int name;
		int attribute;
		string lexeme;

		Token(int name)
		{
			this->name = name;
			attribute = UNDEFINED;
		}

		Token(int name, string lexeme) 
		: Token(name)
		{
			this->lexeme = lexeme;
		}

		Token(int name, int attribute)
		{
			this->name = name;
			this->attribute = attribute;
		}
};