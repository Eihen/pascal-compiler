#ifndef NUMBERTOKEN_H
#define NUMBERTOKEN_H

#include "NumberToken.h"
#include "Token.h"
#include <string>

using namespace std;

class NumberToken : public Token
{
public:
    NumberToken(string val);
    static bool isInteger(string s);
    static bool isFloat(string s);
    static bool isNumber(char c);
    ~NumberToken();
    
    static const int TIPO_FLOAT = 0x10;
    static const int TIPO_INT = 0x11;
};

#endif // NUMBERTOKEN_H
