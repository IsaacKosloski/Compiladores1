#include "token.h"

class STEntry 
{
    public:
        Token* token;
        string lexeme;
        bool reserved;
    
        STEntry();
        STEntry(Token*, string);   
        STEntry(Token*, string, bool);
};
