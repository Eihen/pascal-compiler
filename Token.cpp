#include "Token.h"
#include "Util.h"

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

string Token::getValue() {
    return mValue;
}

int Token::getTipo() {
    return mTipo;
}

Token::~Token() {
}


