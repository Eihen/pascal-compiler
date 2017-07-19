#include "SymbolTableEntry.h"

SymbolTableEntry::SymbolTableEntry(Token token) : SymbolTableEntry(token, 0)
{
}

SymbolTableEntry::SymbolTableEntry(Token token, int scope)
{
    setIdentifier(token.getValue());
    setReferenced(false);
    setScope(scope);
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

bool SymbolTableEntry::isReferenced()
{
    return referenced;
}

int SymbolTableEntry::getScope()
{
    return scope;
}

SymbolTableEntry::~SymbolTableEntry()
{
}
