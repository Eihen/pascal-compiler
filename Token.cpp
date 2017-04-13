#include "Token.h"
#include "Util.h"
#include <iostream>

Token::Token(string val) {
    mValue = val;
    
    if (Util::isKeyword(mValue))
        mTipo = TIPO_KEYWORD;
    else if (mValue.length() == 1 && Util::isSymbol(mValue[0]))
		mTipo = TIPO_SYMBOL;
	else if (Util::isOperator(mValue))
		mTipo = TIPO_OPERADOR;
    else if (Util::isInteger(mValue))
        mTipo = TIPO_INT;
    else if (Util::isFloat(mValue))
        mTipo = TIPO_FLOAT;
    else if (Util::isString(mValue))
        mTipo = TIPO_STRING;
    else 
		mTipo = TIPO_IDENTIFICADOR;
        
	cout << val << " - " << mTipo << endl;
}

string Token::getValue() {
    return mValue;
}

int Token::getTipo() {
    return mTipo;
}

Token::~Token() {
}


