#ifndef VARENTRY_H
#define VARENTRY_H

#include "SymbolTableEntry.h"
#include "../type/Type.h"
#include "../Token.h"

class VarEntry : public SymbolTableEntry
{
public:
    VarEntry(Token token, int scope);
    void setType(Type type);
    Type& getType();
    ~VarEntry();
    
private:
    Type varType;

};

#endif // VARENTRY_H
