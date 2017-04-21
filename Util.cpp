#include "Util.h"
#include "OperatorToken.h"
#include "SymbolToken.h"

Util::Util()
{
}

bool Util::isSeparator(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

bool Util::isDelimiter(char c) {
    return isSeparator(c) || OperatorToken::isOperator(c) || SymbolToken::isSymbol(c);
}

Util::~Util()
{
}

