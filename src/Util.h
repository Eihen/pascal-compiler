#ifndef UTIL_H
#define UTIL_H

#include <string>

using namespace std;

class Helper
{
public:
    Helper();
    ~Helper();
    static bool isSeparator(char c);
    static bool isDelimiter(char c);

};

#endif // UTIL_H
