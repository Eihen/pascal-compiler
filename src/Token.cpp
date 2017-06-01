#include "Token.h"

using namespace std;

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

bool Token::isIdentifier()
{
    return type >= IDENTIFIER;
}

bool Token::isType()
{
    return type >= TYPE_INT && type <= TYPE_BOOLEAN;
}

