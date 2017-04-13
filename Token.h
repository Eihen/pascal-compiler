#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

class Token
{
public:
    static const int TIPO_FLOAT = 0;
    static const int TIPO_INT = 1;
    static const int TIPO_STRING = 2;
    static const int TIPO_IDENTIFICADOR = 3;
    static const int TIPO_KEYWORD = 4;
    
	Token(string val);
    string getValue();
    int getTipo();
	~Token();

};

#endif // TOKEN_H
