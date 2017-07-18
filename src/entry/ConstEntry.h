#ifndef CONSTENTRY_H
#define CONSTENTRY_H

#include "SymbolTableEntry.h"
#include "../Token.h"

class ConstEntry : SymbolTableEntry
{
public:
    ConstEntry(Token token);
    ~ConstEntry();

};

#endif // CONSTENTRY_H
