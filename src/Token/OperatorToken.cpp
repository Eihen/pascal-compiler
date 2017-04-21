#include "OperatorToken.h"

OperatorToken::OperatorToken(string val) : Token(val)
{
    setTipo(TIPO_OPERADOR);
}

bool OperatorToken::isOperator(char ch) {
    return ch == ':' || ch == '=' || ch == '%' ||
           ch == '+' || ch == '-'  || ch == '/' || ch == '*' || 
           ch == '<' || ch== '>' || 
           ch == '&' || ch == '|' || ch == '!' || ch == '~';
}

bool OperatorToken::operadorPrefixo(char ch) {
    return ch == ':' || ch == '<' || ch == '>';
}

bool OperatorToken::isOperator(string operador) {
	return (operador.length() == 1 && isOperator(operador[0])) || 
	operador == "<<" || operador == ">>" ||
	operador == ">=" || operador == "<=" || operador == "<>" ||
	operador == ":=";
}

OperatorToken::~OperatorToken()
{
}

