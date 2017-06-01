#include "Token.h"
#include "Parser.h"

Parser::Parser()
{
	getToken();
	progrm();
}	

void Parser::getToken()
{
	//TODO
	//Armazar o tipo do Token na variável "simbolo"
}

void Parser::constant()
{
	if(simbolo == LIT_STRING || simbolo == LIT_INT || simbolo == LIT_FLOAT /*ou identificador de constante*/)
		getToken();
	else
		if(simbolo == OP_PLUS || simbolo == OP_MINUS)
		{
			getToken();
			if(simbolo != LIT_INT && simbolo != LIT_FLOAT /*ou identificador de constante*/)
				trataErro();
		}
		else
			trataErro();
}

void Parser::sitype()
{
	/*if(simbolo == -1) //Trocar por identficador de tipo
		getToken();
	else
		if(simbolo == SMB_OPEN_PARENT)
			if(simbolo >= IDENTIFIER)
				if(simbolo == SMB_COMMA || simbolo == SMB_CLOSE_PARENT)
					
				else
					trataErro();
			else
				trataErro();
		else
			constant();*/
}

void Parser::filist()
{
}

void Parser::infipo()
{
}

void Parser::siexpr()
{
}

void Parser::expr()
{
}

void Parser::palist()
{
}

void Parser::statm()
{
}

void Parser::progrm()
{
}

void Parser::trataErro()
{
}
	
Parser::~Parser()
{
}

