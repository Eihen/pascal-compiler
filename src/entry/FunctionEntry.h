#ifndef FUNCTIONENTRY_H
#define FUNCTIONENTRY_H

#include "ProcedureEntry.h"
#include "../Token.h"

class FunctionEntry : public ProcedureEntry
{
public:
    FunctionEntry(Token token, int scope);
    ~FunctionEntry();

};

#endif // FUNCTIONENTRY_H
