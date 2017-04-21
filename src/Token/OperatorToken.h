#ifndef OPERATORTOKEN_H
#define OPERATORTOKEN_H

#include <string>
#include "Token.h"

using namespace std;

class OperatorToken : public Token
{
public:
    OperatorToken(string val);
    static bool isOperator(char c);
    static bool isOperator(string operador);
    static bool operadorPrefixo(char c);
    ~OperatorToken();
    
    static const int TIPO_OPERADOR = 0x20;

};

#endif // OPERATORTOKEN_H
