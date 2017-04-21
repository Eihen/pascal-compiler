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
    static bool isDelimiter(char c);

};

#endif // UTIL_H
