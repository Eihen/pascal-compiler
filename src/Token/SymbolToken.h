#ifndef SYMBOLTOKEN_H
#define SYMBOLTOKEN_H

#include <string>
#include "Token.h"

using namespace std;

class SymbolToken : public Token
{
public:
    SymbolToken(string val);
    static bool isSymbol(char c);
    ~SymbolToken();
    
    static const int TIPO_SIMBOLO = 0x40;

};

#endif // SYMBOLTOKEN_H
