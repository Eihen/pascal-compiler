#include "Token.h"

string Token::getValue()
{
    return value;
}

int Token::getType()
{
    return type;
}

int Token::getLine()
{
    return line;
}

int Token::getColumn()
{
    return column;
}

void Token::setType(int _type)
{
    type = _type;
}

