#include "ConstEntry.h"

ConstEntry::ConstEntry(Token token, int scope, string value) : SymbolTableEntry(token, scope)
{
    this->value = value;
}

ConstEntry::~ConstEntry()
{
}

string ConstEntry::getValue()
{
    return this->value;
}

