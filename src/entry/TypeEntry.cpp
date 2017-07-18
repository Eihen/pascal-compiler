#include "TypeEntry.h"

TypeEntry::TypeEntry(Token token) : SymbolTableEntry(token)
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

