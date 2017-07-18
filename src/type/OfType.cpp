#include "OfType.h"

OfType::OfType(int code, Type ofType) : Type(code), ofType(ofType)
{
}

Type OfType::getOfType()
{
    return this->ofType;
}

OfType::~OfType()
{
}
