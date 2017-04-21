#include "NumberToken.h"

NumberToken::NumberToken(string val) : Token(val) {
    if (isInteger(val))
        setTipo(TIPO_INT);
    else if (isFloat(val))
        setTipo(TIPO_FLOAT);
}

bool NumberToken::isInteger(string s) {
	string numbers = "0123456789";
	
	//Assim não fica chamando .length() toda hora e comparação com 0 é mais rápido
	for (int i = s.length() - 1; i >= 0; i--)
	{
		if (numbers.find(s[i]) == string::npos)
		{
			return false;
		}
	} 

    return true;
}

bool NumberToken::isFloat(string s) {
	string numbers = "0123456789";
	bool hasDot = false;
	
	//Não pode começar nem terminar com ".", já aproveitei e verifiquei se é número
	if (numbers.find(s[0]) == string::npos || s[0] == '.' || numbers.find(s[s.length() - 1]) == string::npos || s[s.length() - 1] == '.')
	{
		return false;
	}
	
	for (int i = s.length() - 2; i > 0; i--)
	{
		//Não pode ter dois "."s
		if (s[i] == '.')
		{
			if (hasDot)
			{
				return false;
			}
			else
			{
				hasDot = true;
			}
		}
		else if (numbers.find(s[i]) == string::npos)
		{
			return false;
		}
	}
    return true;
}

bool NumberToken::isNumber(char c) {
    return c >= '0' && c <= '9';
}

NumberToken::~NumberToken()
{
}

