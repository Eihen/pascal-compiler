#include "Util.h"
#include <iostream>

Util::Util()
{
}

bool Util::isSeparator(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

bool Util::isSymbol(char ch) {
    return ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch ==';' || ch == ',' || ch == '[' || ch == ']';
}

bool Util::isOperator(char ch) {
    return ch == ':' || ch == '=' || ch == '%' ||
           ch == '+' || ch == '-'  || ch == '/' || ch == '*' || 
           ch == '<' || ch== '>' || 
           ch == '&' || ch == '|' || ch == '!' || ch == '~';
}

bool Util::isOperator(string operador) {
	return (operador.length() == 1 && isOperator(operador[0])) || 
	operador == "<<" || operador == ">>" ||
	operador == ">=" || operador == "<=" || operador == "<>" ||
	operador == ":=";
}

bool Util::operadorPrefixo(char ch) {
    return ch == ':' || ch == '<' || ch == '>';
}

bool Util::isString(string s) {
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

bool Util::isInteger(string s) {
	string numbers = "0123456789";
	
	//Assim não fica chamando .length() toda hora e comparação com 0 é mais rápido
	for (int i = s.length() - 1; i >= 0; i--)
	{
		if (numbers.find(s[i]) == string::npos)
		{
			return false;
		}
	} 
	cout << s << endl;
    return true;
}

bool Util::isFloat(string s) {
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

bool Util::isKeyword(string s) {
	set<string> keywords = {"and", "array", "asm", "begin", "break", "case", "const", "constructor", "continue", "destructor", "div", "do", "downto", "else", 
						 "end", "false", "file", "for", "function", "goto", "if", "implementation", "in", "inline", "interface", "label", "mod", "nil", "not", 
						 "object", "of", "on", "operator", "or", "packed", "procedure", "program", "record", "repeat", "set", "shl", "shr", "string", "then", 
						 "to", "true", "type", "unit", "until", "uses", "var", "while", "with", "xor"};
	return keywords.find(s) != keywords.end();
}

Util::~Util()
{
}

