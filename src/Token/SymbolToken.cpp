#include "SymbolToken.h"

SymbolToken::SymbolToken(string val) : Token(val)
{
    setTipo(TIPO_SIMBOLO);
}

bool SymbolToken::isSymbol(char ch) {
    return ch == '(' || ch == ')' || ch ==';' || ch == ',' || ch == '[' || ch == ']' || ch == '.';
}

SymbolToken::~SymbolToken()
{
}

