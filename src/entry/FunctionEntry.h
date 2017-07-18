#ifndef FUNCTIONENTRY_H
#define FUNCTIONENTRY_H

#include "ProcedureEntry.h"
#include "../Token.h"

class FunctionEntry : ProcedureEntry
{
public:
    FunctionEntry(Token token);
    ~FunctionEntry();

};

#endif // FUNCTIONENTRY_H
