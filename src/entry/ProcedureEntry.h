#ifndef PROCEDUREENTRY_H
#define PROCEDUREENTRY_H

#include "SymbolTableEntry.h"
#include "../Token.h"
#include <list>

class ProcedureEntry : public SymbolTableEntry
{
public:
    ProcedureEntry(Token token, int scope);
    void setParams(list<SymbolTableEntry> params);
    list<SymbolTableEntry> getParams();
    ~ProcedureEntry();
private:
    list<SymbolTableEntry> params;

};

#endif // PROCEDUREENTRY_H
