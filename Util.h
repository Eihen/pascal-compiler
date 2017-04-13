#ifndef UTIL_H
#define UTIL_H

#include <string>

using namespace std;

class Util
{
public:
    Util();
    ~Util();
    static bool isSeparator(char c);
    static bool isComma(char c);
    static bool isSymbol(char c);
    static bool isOperator(char c);
    static bool isDelimiter(char c);
    static bool isInteger(string s);
    static bool isFloat(string s);
    static bool isString(string s);
    static bool isKeyword(string s);

};

#endif // UTIL_H
