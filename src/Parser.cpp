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
	//Armazar o token na variável token e o tipo do Token na variável "type"
}

void Parser::constant()
{
	if(type == LIT_STRING || type == LIT_INT || type == LIT_FLOAT || token->isIdentifier() /*identificador de constante*/)
		getToken();
	else
		if(type == OP_PLUS || type == OP_MINUS)
		{
			getToken();
			if(type != LIT_INT && type != LIT_FLOAT && !token->isIdentifier() /*identificador de constante*/)
				trataErro("Literal esperado");
		}
		else
			trataErro("Operador + ou - esperado");
}

void Parser::sitype()
{
	if(token->isIdentifier() /*identificador de tipo*/) 
		getToken();
	else {
        if(type == SMB_OPEN_PARENT) {
            do {
                getToken();
                if (token->isIdentifier()) {
                    getToken();
                    if (type != SMB_COMMA && type != SMB_CLOSE_PARENT) {
                        trataErro("Vírgula ou parenteses esperado");
                        return;
                    }
                }
                else {
                    trataErro("Identificador esperado");
                    return;
                }
            } while (type == SMB_COMMA);
            //token nesse ponto é )
            getToken();
        }
		else {
            constant();
            //TODO ".." deveria ser um token
            getToken();
            if (type == SMB_DOT) {
                getToken();
                if (type == SMB_DOT) {
                    getToken();
                    constant();
                }
                else
                     trataErro("Delimitador .. esperado");
            }
            else
                trataErro("Delimitador .. esperado");
        }
    }
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

void Parser::read_type() 
{
    
}

void Parser::block()
{
    //LABEL
    if (type == KW_LABEL) {
        do {
            getToken();
            if (type == LIT_FLOAT || type == LIT_INT) {
                getToken();
                if (type != SMB_COMMA && type != SMB_SEMICOLON) {
                    trataErro("Vírgula ou ponto e vírgula esperado");
                    return;
                }
            }
            else {
                trataErro("Literal numérico esperado");
                return;
            }
        } while (type == SMB_COMMA);
        
        //nesse ponto, o token é um ;
        getToken();
    }
    //CONST
    else if (type == KW_CONST) {
        getToken();
        if (token->isIdentifier()) {
            do {
                getToken();
                if (type == OP_EQUALS) {
                    getToken();
                    constant();
                    if (type == SMB_SEMICOLON) {
                        getToken();
                        //se for identificador: continuará o laço; caso contrário, continuará leitura do bloco
                    }
                }
                else {
                    trataErro("Operador = esperado");
                    break;
                }
            } while (token->isIdentifier());
        }
        else 
            trataErro("Identificador esperado");
    }
    //TYPE
    else if (type == KW_TYPE) {
        getToken();
        if (token->isIdentifier()) {
            do {
                getToken();
                if (type == OP_EQUALS) {
                    getToken();
                    read_type();
                    if (type == SMB_SEMICOLON) {
                        getToken();
                        //se for identificador: continuará o laço; caso contrário, continuará leitura do bloco
                    }
                }
                else {
                    trataErro("Operador = esperado");
                    break;
                }
            } while (token->isIdentifier());
        }
        else 
            trataErro("Identificador esperado");
    }
    //VAR
    else if (type == KW_VAR) {
    
        getToken();
        if (token->isIdentifier()) {
            do {
                getToken();
                if (type == SMB_COMMA) {
                    getToken();
                    if (!token->isIdentifier()) //nesse ponto, identificador é obrigatório
                        trataErro("Identificador esperado");
                }
                else if (type == SMB_COLON) {
                    read_type();
                    if (type == SMB_SEMICOLON) {
                        getToken();
                        //se não for identificador, sairá do laço
                    }
                }
            } while (token->isIdentifier());
        }
        else 
            trataErro("Identificador esperado");
    }
    //PROCEDURE
    else if (type == KW_PROCEDURE) {
        getToken();
        if (token->isIdentifier()) {
            getToken();
            palist();
            if (type == SMB_SEMICOLON) {
                getToken();
                block();
                if (type == SMB_SEMICOLON)
                    getToken();
                else
                    trataErro("Ponto e vírgula esperado");
            }
            else
                trataErro("Ponto e vírgula esperado");
        }
        else
            trataErro("Identificador esperado");
    }
    //FUNCTION
    else if (type == KW_FUNCTION) {
        getToken();
        if (token->isIdentifier()) {
            getToken();
            palist();
            if (type == SMB_COLON) {
                getToken();
                if (token->isType()) {
                    getToken();
                    if (type == SMB_SEMICOLON) {
                        getToken();
                        block();
                        if (type == SMB_SEMICOLON)
                            getToken();
                        else
                            trataErro("Ponto e vírgula esperado");
                    }
                    else
                        trataErro("Ponto e vírgula esperado");
                }
                else
                    trataErro("Identificador de tipo esperado");
            }
            else 
                trataErro(": esperado");
        }
        else
            trataErro("Identificador esperado");
    }
    //BEGIN
    else if (type == KW_BEGIN) {
        do {
            getToken();
            statm();
            getToken();
        } while (type == SMB_SEMICOLON);
        
        if (type == KW_END)
            getToken();
        else
            trataErro("End esperado");
            
        return;
    }
    else 
        trataErro("Label, Const, Type, Var, Procedure, Function ou Begin esperado");
    block();
}

void Parser::progrm()
{
    if (type == KW_PROGRAM) {
        getToken();
        if (token->isIdentifier()) {
            getToken();
            if (type == SMB_OPEN_PARENT) {
                do {
                    getToken();
                    if (token->isIdentifier()) {
                        getToken();
                        if (type != SMB_COMMA && type != SMB_CLOSE_PARENT) {
                            trataErro("Vírgula ou parenteses esperado");
                            return;
                        }
                    }
                    else {
                        trataErro("Identificador esperado");
                        return;
                    }
                } while (type == SMB_COMMA);
                
                //token nesse ponto é )
                getToken();
                if (type == SMB_SEMICOLON) {
                    getToken();
                    block();
                    if (type != SMB_DOT)
                        trataErro("Ponto esperado");
                }
                else
                    trataErro("Ponto e vírgula esperado");
                    
                
            }
            else
                trataErro("Parenteses ( esperado");
        }
        else
            trataErro("Identificador esperado");
    }
    else
        trataErro("Program esperado");
}

void Parser::trataErro(string message)
{
    message += " (linha: " + to_string(token->getLine()) + ", coluna: " + to_string(token->getColumn()) + ")";
}
	
Parser::~Parser()
{
}

