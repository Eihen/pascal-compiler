#include "Parser.h"

using namespace std;

Parser::Parser(TokenQueue* _tokenQueue)
{
	tokenQueue = _tokenQueue;
	getToken();
	progrm();
}	

void Parser::getToken()
{
	token = tokenQueue->dequeue();
	type = token->getType();
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
    //number
    if (token->isNumber()) {
        getToken();
        if (type != SMB_COLON)
            trataErro(": esperado");
    }
    //TODO identifier
    else if (token->isIdentifier()) {
    }
    //begin
    else if (type == KW_BEGIN) {
        do {
            getToken();
            statm();
            getToken();
        } while (type == SMB_SEMICOLON);
        
        if (type != KW_END)
            trataErro("end esperado");
    }
    //if
    else if (type == KW_IF) {
        getToken();
        expr();
        getToken();
        if (type == KW_THEN) {
            getToken();
            statm();
            getToken();
            if (type == KW_ELSE) {
                getToken();
                statm();
            }
            //TODO lambda (sem getToken())
        }
        else 
            trataErro("then esperado");
    }
    //case
    else if (type == KW_CASE) {
        getToken();
        expr();
        getToken();
        if (type == KW_OF) {
            do {
                getToken();
                if (type == LIT_STRING || token->isIdentifier() /* constant identifier */ || token->isNumber())
                    getToken();
                else if (type == OP_PLUS || type == OP_MINUS) {
                    getToken();
                    if (token->isIdentifier() /* constant identifier */ || token->isNumber()) 
                        getToken();
                    else {
                        trataErro("constante esperada");
                        break;
                    }
                }
                else {
                    trataErro("string, constante, +, - ou número esperado");
                    break;
                }
                
                //, or :
                if (type == SMB_COMMA)
                    continue;
                    
                if (type == SMB_COLON) {
                    getToken();
                    statm();
                    getToken();
                    //; ou end esperado nesse ponto
                }
                else {
                    trataErro(", ou : esperado");
                    break;
                }
                
            } while (type == SMB_SEMICOLON);
            
            if (type != KW_END)
                trataErro("end esperado");
        }
        else
            trataErro("of esperado");
    }
    //while
    else if (type == KW_WHILE) {
        getToken();
        expr();
        getToken();
        if (type == KW_DO) {
            getToken();
            statm();
        }
        else
            trataErro("do esperado");
    }
    //repeat
    else if (type == KW_REPEAT) {
        do {
            getToken();
            statm();
            getToken();
        } while (type == SMB_SEMICOLON);
        
        //until
        if (type == KW_UNTIL) {
            getToken();
            expr();
        }
        else
            trataErro("until esperado");
    }
    //for
    else if (type == KW_FOR) {
        getToken();
        if (token->isIdentifier()) { //variable identifier
            getToken();
            infipo();   
            getToken();
            if (type == OP_ASSIGN) {
                getToken();
                expr();
                getToken();
                if (type == KW_TO || type == KW_DOWNTO) {
                    getToken();
                    expr();
                    getToken();
                    if (type == KW_DO) {
                        getToken();
                        statm();
                    }
                    else
                        trataErro("do esperado");
                }
                else
                    trataErro("to ou downto eesperado");
            }
            else
                trataErro(":= esperado");
            
        }
        else
            trataErro("Variável esperada");
    }
    //with
    else if (type == KW_WITH) {
        do {
            getToken();
            if (token->isIdentifier()) { //variable identifier
                getToken();
                infipo();
                getToken();
                //se este token for uma vírgula, continuará o for
            }
            else {
                trataErro("Variável esperada");
                break;
            }
        } while (type == SMB_COMMA);
        
        //"do" esperado após leitura das variáveis
        if (type == KW_DO) {
            getToken();
            statm();
        }
        else
            trataErro("do esperado");
    }
    //goto
    else if (type == KW_GOTO) {
        getToken();
        if (type != LIT_INT)
            trataErro("Número inteiro esperado");
    }
}

void Parser::read_type() 
{
    if (!token->isType()) {
        if (type == KW_PACKED)
            getToken();
        //ARRAY
        if (type == KW_ARRAY) {
            getToken();
            if (type == SMB_OPEN_BRACKET) {
                do {
                    getToken();
                    sitype();
                    getToken();
                } while (type == SMB_COMMA);
                
                if (type == SMB_CLOSE_BRACKET) {
                    getToken();
                    if (type == KW_OF) {
                        getToken();
                        read_type();
                    }
                    else
                        trataErro("of esperado");
                }
                else
                    trataErro("] esperado");
                
            }
            else
                trataErro("[ esperado");
        }
        //FILE
        else if (type == KW_FILE) {
            getToken();
            if (type == KW_OF) {
                read_type();
            }
            else
                trataErro("of esperado");
        }
        //SET
        else if (type == KW_SET) {
            getToken();
            if (type == KW_OF) {
                sitype();
            }
            else
                trataErro("of esperado");
        }
        //RECORD
        else if (type == KW_RECORD) {
            getToken();
            filist();
            getToken();
            if (type != KW_END) 
                trataErro("end esperado");
        }
        else
            sitype();
    }
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

