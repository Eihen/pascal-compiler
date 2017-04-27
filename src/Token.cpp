#include "Token.h"

string Token::getValue()
{
    return value;
}

int Token::getType()
{
    return type;
}

void Token::setType(int _type)
{
    type = _type;
}

