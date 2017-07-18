#include "Type.h"

Type::Type()
{
    this->code = 0;
}

Type::Type(int code)
{
    this->code = code;
}

int Type::getCode()
{
    return code;
}

Type::~Type()
{
}

