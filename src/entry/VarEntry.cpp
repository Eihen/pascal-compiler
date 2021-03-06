#include "VarEntry.h"

VarEntry::VarEntry(Token token, int scope) : SymbolTableEntry(token, scope), varType(0)
{
}

void VarEntry::setType(Type type)
{
    this->varType = type;
}

Type& VarEntry::getType()
{
    return varType;
}

VarEntry::~VarEntry()
{
}

void VarEntry::setMemoryPosition(int memoryPosition)
{
    this->memoryPosition = memoryPosition;
}

int VarEntry::getMemoryPosition()
{
    return this->memoryPosition;
};

