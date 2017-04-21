#include "StringToken.h"

StringToken::StringToken(string val) : Token(val)
{
    if (isKeyword(val))
        setTipo(TIPO_KEYWORD);
    else if (isString(val))
        setTipo(TIPO_STRING);
    else
        setTipo(TIPO_IDENTIFICADOR);
}

StringToken::~StringToken()
{
}

bool StringToken::isString(string s) {
	bool unescaped = false;
	
    //inicia com ' e termina com '
	if (s[0] != '\'' || s[s.length() - 1] != '\'')
	{
		return false;
	}
	
	//sem ' não escapados no meio
	for (int i = s.length() - 2; i > 0; i--)
	{
		if (s[i] == '\'')
		{
			//Se precisar escapar marca que foi escapado, se não marca que precisa escapar
			unescaped = !unescaped;
		}
		else if (s[i] != '\'' && unescaped) //Se o char não for um apostrofo e precisar escapar, string inválida
		{
			return false;
		}
	}
	return !unescaped; //Se o último char precisar ser escapado, string inválida
}

bool StringToken::isKeyword(string s) {
    static set<string> keywords = {"and", "array", "asm", "begin", "break", "case", "const", "constructor", "continue", "destructor", "div", "do", "downto", "else", 
						 "end", "false", "file", "for", "function", "goto", "if", "implementation", "in", "inline", "interface", "label", "mod", "nil", "not", 
						 "object", "of", "on", "operator", "or", "packed", "procedure", "program", "record", "repeat", "set", "shl", "shr", "string", "then", 
						 "to", "true", "type", "unit", "until", "uses", "var", "while", "with", "xor"};
	return keywords.find(s) != keywords.end();
}

bool StringToken::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

