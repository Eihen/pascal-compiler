#include "Token.h"

string Token::getValue()
{
    return mValue;
}

int Token::getTipo()
{
    return mTipo;
}

void Token::setTipo(int tipo)
{
    mTipo = tipo;
}

