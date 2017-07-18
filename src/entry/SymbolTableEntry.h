#ifndef SYMBOLTABLEENTRY_H
#define SYMBOLTABLEENTRY_H

#include <string>

using namespace std;

class SymbolTableEntry
{
public:
    SymbolTableEntry();
    void setIdentifier(const string& identifier);
    void setReferenced(bool referenced);
    void setScope(int scope);
    
    const string& getIdentifier() const;
    bool isReferenced() const;
    int getScope() const;
    ~SymbolTableEntry();

private:
    string identifier;
    int scope;
    bool referenced;
};

#endif // SYMBOLTABLEENTRY_H
