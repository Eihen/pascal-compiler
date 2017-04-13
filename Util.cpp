#include "Util.h"

Util::Util()
{
}

bool Util::isSeparator(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

bool Util::isComma(char ch) {
    return ch == ',';
}

bool Util::isSymbol(char ch) {
    return ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch ==';' || ch == '[' || ch == ']';
}

bool Util::isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '=' || ch == '/' || ch =='*' || ch =='%' || ch =='<' || ch=='>';
}

bool Util::isDelimiter(char ch) {
    return isSeparator(ch) || isComma(ch) || isSymbol(ch) || isOperator(ch);
}

bool Util::isString(string s) {
    //inicia com " e termina com ", sem outros " no meio?
}

bool Util::isInteger(string s) {
    return true;
}

bool Util::isFloat(string s) {
    return true;
}

bool Util::isKeyword(string s) {
    return true;
}

Util::~Util()
{
}

