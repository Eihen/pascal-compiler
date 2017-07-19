#include "TypeEntry.h"

TypeEntry::TypeEntry(Token token, int scope) : SymbolTableEntry(token, scope)
{
    static int CODE_COUNTER = 150000;
    code = ++CODE_COUNTER;
}

TypeEntry::getCode()
{
    return code;
}

TypeEntry::~TypeEntry()
{
}

