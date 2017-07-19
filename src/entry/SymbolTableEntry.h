#ifndef SYMBOLTABLEENTRY_H
#define SYMBOLTABLEENTRY_H

#include <string>
#include "../Token.h"

using namespace std;

class SymbolTableEntry
{
public:
    SymbolTableEntry(Token token);
    void setIdentifier(const string& identifier);
    void setReferenced(bool referenced);
    void setScope(int scope);
    
    const string& getIdentifier() const;
    bool isReferenced();
    int getScope();
    virtual ~SymbolTableEntry();

private:
    string identifier;
    int scope;
    bool referenced;
};

#endif // SYMBOLTABLEENTRY_H
