#ifndef FIELDENTRY_H
#define FIELDENTRY_H

#include "SymbolTableEntry.h"
#include "../Token.h"

class FieldEntry : public SymbolTableEntry
{
public:
    FieldEntry(Token token);
    ~FieldEntry();

};

#endif // FIELDENTRY_H
