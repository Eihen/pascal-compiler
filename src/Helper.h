#ifndef HELPER_H
#define HELPER_H

#include <string>

using namespace std;

class Helper
{
public:
    Helper();
    ~Helper();
    static bool isSeparator(char c);
    static bool isDelimiter(char c);
	static bool isNumber(char c);
	static bool isLetter(char c);
	static int isKeyword(string word);
	static bool isSymbolPrefix(char c);
	static int isSymbol(string word);
};

#endif // HELPER_H
