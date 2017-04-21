#ifndef STRINGTOKEN_H
#define STRINGTOKEN_H

#include <string>
#include <set>
#include "Token.h"

using namespace std;

class StringToken : public Token
{
public:
    StringToken(string val);
    ~StringToken();
    static bool isKeyword(string s);
    static bool isString(string s);
    static bool isLetter(char c);
    
    static const int TIPO_STRING = 0x00;
    static const int TIPO_IDENTIFICADOR = 0x01;
    static const int TIPO_KEYWORD = 0x02;

};

#endif // STRINGTOKEN_H
