#ifndef TABLEROW_H
#define TABLEROW_H

#include "Token.h"

namespace std {
    enum { 
		CONST_IDENTIFIER, FUNCTION_IDENTIFIER, PROCEDURE_IDENTIFIER, TYPE_IDENTIFIER, VAR_IDENTIFIER, FIELD_IDENTIFIER
    };
     
    class TableRow
    {
    private:
            Token token;
            int type;
        public:
            TableRow(Token _token, int _type);
            int getType();
            Token getToken();
            ~TableRow();
    
            

}; 
}

#endif // TABLEROW_H
