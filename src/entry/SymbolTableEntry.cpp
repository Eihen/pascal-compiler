#include "SymbolTableEntry.h"

SymbolTableEntry::SymbolTableEntry(Token token)
{
    setIdentifier(token.getValue());
    setReferenced(false);
    setScope(0);
}

void SymbolTableEntry::setIdentifier(const string& identifier)
{
    this->identifier = identifier;
}

void SymbolTableEntry::setReferenced(bool referenced)
{
    this->referenced = referenced;
}

void SymbolTableEntry::setScope(int scope)
{
    this->scope = scope;
}

const string& SymbolTableEntry::getIdentifier() const
{
    return identifier;
}

bool SymbolTableEntry::isReferenced() const
{
    return referenced;
}

int SymbolTableEntry::getScope() const
{
    return scope;
}

SymbolTableEntry::~SymbolTableEntry()
{
}
