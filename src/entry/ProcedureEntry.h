#ifndef PROCEDUREENTRY_H
#define PROCEDUREENTRY_H

#include "SymbolTableEntry.h"
#include "../Token.h"

class ProcedureEntry : SymbolTableEntry
{
public:
    ProcedureEntry(Token token);
    ~ProcedureEntry();

};

#endif // PROCEDUREENTRY_H
