#ifndef TYPEENTRY_H
#define TYPEENTRY_H

#include "SymbolTableEntry.h"
#include "../Token.h"

class TypeEntry : public SymbolTableEntry
{
public:
    TypeEntry(Token token, int scope);
    int getCode();
    ~TypeEntry();
private:
    int code;
};

#endif // TYPEENTRY_H
