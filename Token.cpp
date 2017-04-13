#include "Token.h"
#include "Util.h"

const int TIPO_FLOAT = 0;
const int TIPO_INT = 1;
const int TIPO_STRING = 2;
const int TIPO_IDENTIFICADOR = 3;
const int TIPO_KEYWORD = 4;

int mTipo;
string mValue;
    
Token::Token(string val) {
    mValue = val;
    if (Util::isKeyword(mValue))
        mTipo = TIPO_KEYWORD;
    else if (Util::isInteger(mValue))
        mTipo = TIPO_INT;
    else if (Util::isFloat(mValue))
        mTipo = TIPO_FLOAT;
    else if (Util::isString(mValue))
        mTipo = TIPO_STRING;
}

Token::~Token() {
}


