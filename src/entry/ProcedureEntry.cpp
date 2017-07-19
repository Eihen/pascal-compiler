#include "ProcedureEntry.h"

ProcedureEntry::ProcedureEntry(Token token, int scope) : SymbolTableEntry(token, scope)
{
}

ProcedureEntry::~ProcedureEntry()
{
}

void ProcedureEntry::setParams(list <SymbolTableEntry> params)
{
    this->params = params;
}

list <SymbolTableEntry> ProcedureEntry::getParams()
{
    return params;
}

