#include<iostream>
#include<ctype.h>
#include<string.h>

using namespace std;


/*UNDEFINED, ID, INTEGER_LITERAL, OP, <, >, <=, >=, +, -, *, /, %, =, ==, !=,
SEP, (, ), [, ], {, }, ;, :, ., ,, LEFT_INVERTED_COMMAS, RIGHT_INVERTED_COMMAS, END_OF_FILE*/
enum Names { UNDEFINED, ID, INTEGER_LITERAL, STRING_LITERAL, OP, LESS_THAN, GREATER_THAN, LESS_OR_EQUAL,
GREATER_OR_EQUAL, ADDITION, SUBTRACTION, ASTERISK, BAR, MODULAR, ASSIGNMENT, EQUAL, NOT_EQUAL,
SEP, LEFT_PARENTHESE, RIGHT_PARENTHESE, LEFT_BRACKET, RIGHT_BRACKET, LEFT_BRACE, RIGHT_BRACE,
SEMICOLON, COLON, DOT, COMMA_LITERAL, LEFT_INVERTED_COMMAS, RIGHT_INVERTED_COMMAS, END_OF_FILE,
CLASS, EXTENDS, INT, STRING, BREAK, PRINT, READ, RETURN, SUPER, IF, ELSE, FOR, NEW, CONSTRUCTOR
};


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
