#include "Parser.h"

using namespace std;

Parser::Parser(TokenQueue* _tokenQueue)
{
	try
	{
		tokenQueue = _tokenQueue;
		getToken();
		progrm();
	}
	catch(int e)
	{
		trataErro("Fim do programa não encontrado");
	}
	
	//Verifica se existem erros na compilação do programa, em caso positivo exibe os erros
	if(errorQueue.empty())
		cout << "Compilação terminada com sucessso" << endl;
	else
		while(!errorQueue.empty())
		{
			cout << errorQueue.front() << endl;
			errorQueue.pop();
		}
}	

bool Parser::isIdentifier(int desiredType)
{
    if (token.isIdentifier()) 
    {
        //ToDo @lucasfernog disse que ia tirar isso, se alguém o fizer tirar o que ta marcado no Token.h
        map<Token, TableRow>::iterator it = table.find(token);
        if (it != table.end())
            return it->second.getType() == desiredType;
    }
    return false;
}

void Parser::getToken()
{
	//Pega próxima token
	token = tokenQueue->dequeue();
	type = token.getType();
	
	//Token de erro - adicionar na lista de errros
	while(type >= ERR_CHAR && type <= ERR_FORMAT)
	{
		switch(type)
		{
			case ERR_CHAR:
				trataErro("Caracter inválido");
			break;
			case ERR_SIZE:
				trataErro("Ident. com muitos carac.");
			break;
			case ERR_END_FILE:
				trataErro("Fim inesperado de arquivo");
			break;
			case ERR_FORMAT:
				trataErro("Cadeia inválida");
			break;
			default: break;
		}
		//Pega próxima token
		token = tokenQueue->dequeue();
		type = token.getType();
	}
}

bool Parser::verify_and_get(bool condition)
{
	if(condition)
		getToken();
	return condition;
}

void Parser::constant()
{
	if(type == LIT_STRING || type == LIT_INT || type == LIT_FLOAT || isIdentifier(CONST_IDENTIFIER))
		getToken();
	else
		if(type == OP_PLUS || type == OP_MINUS)
		{
			getToken();
			if(type == LIT_INT || type == LIT_FLOAT || isIdentifier(CONST_IDENTIFIER))
				getToken();
			else
				trataErro("Literal esperado");
		}
		else
			trataErro("Operador + ou - esperado");
}

void Parser::sitype()
{
	if(isIdentifier(TYPE_IDENTIFIER) || (type >= TYPE_INT && type <= TYPE_BOOLEAN)) 
		getToken();
	else {
        if(type == SMB_OPEN_PARENT) {
            do {
                getToken();
                if (token.isIdentifier()) {
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
            if (type == SMB_DOUBLE_DOT) {
                getToken();
                constant();
            }
            else
                trataErro("Delimitador .. esperado");
        }
    }
}

void Parser::aux_filist_p1()
{
    //TODO if else incorreto
	if(token.isIdentifier())
	{
		getToken();
		if(type == OP_COLON)
		{
			getToken();
			if(isIdentifier(TYPE_IDENTIFIER) || (type >= TYPE_INT && type <= TYPE_BOOLEAN))
			{
				getToken();
				if(type == KW_OF)
				{
					getToken();
					aux_filist_p2();
				}
			}
			else
				trataErro("Identificador de tipo esperado");
		}
		else
			trataErro("Símbolo : esperado");
	}
	else
		if(isIdentifier(TYPE_IDENTIFIER) || (type >= TYPE_INT && type <= TYPE_BOOLEAN))
		{
			getToken();
			if(type == KW_OF)
			{
				getToken();
				aux_filist_p2();
			}
		}
		else
			trataErro("Identificador ou identificador de tipo esperado");
}

void Parser::aux_filist_p2()
{
	if(type == LIT_STRING || isIdentifier(CONST_IDENTIFIER) || type == LIT_INT || type == LIT_FLOAT)
	{
		getToken();
		aux_filist_p3();
	}
	else
		if(type == OP_PLUS || type == OP_MINUS)
		{
			getToken();
			if(isIdentifier(CONST_IDENTIFIER) || type == LIT_INT || type == LIT_FLOAT)
			{
				getToken();
				aux_filist_p3();
			}
		}
		else
			if(type == SMB_SEMICOLON)
			{
				getToken();
				aux_filist_p2();
			}
}

void Parser::aux_filist_p3()
{
	if(type == SMB_COMMA)
	{
		getToken();
		aux_filist_p2();
	}
	else
		if(type == OP_COLON)
		{
			getToken();
			if(type == SMB_OPEN_PARENT)
			{
				getToken();
				filist();
				if(type == SMB_CLOSE_PARENT)
				{
					getToken();
					if(type == SMB_SEMICOLON)
					{
						getToken();
						aux_filist_p2();
					}
				}
				else
					trataErro("Símbolo ) esperado");
			}
			else
				trataErro("Símbolo ( esperado");
		}
		else
			trataErro("Símbolo : ou , esperado");
}

void Parser::filist()
{
	if(token.isIdentifier())
	{
        //registra token na tabela
        table.insert(pair<Token, TableRow>(token, TableRow(token, FIELD_IDENTIFIER)));
		getToken();
		if(type == SMB_COMMA)
		{
			getToken();
			filist();
		}
		else
			if(type == OP_COLON)
			{
				getToken();
				if(type == SMB_SEMICOLON)
				{
					getToken();
					filist();
				}
				else
					if(type == KW_CASE)
					{
						getToken();
						aux_filist_p1();
					}
			}
			else
				trataErro("Símbolo : ou , esperado");
	}
	else
		if(type == KW_CASE)
		{
			getToken();
			aux_filist_p1();
		}
}

void Parser::infipo()
{
	if(type == SMB_OPEN_BRACKET)
	{
		do
		{
			getToken();
			expr();
		}while(type == SMB_COMMA);
		if(type == SMB_CLOSE_BRACKET)
		{
			getToken();
			infipo();
		}
		else
			trataErro("Símbolo ] ou , esperado");
	}
	else 
		if(type ==  SMB_DOT)
		{
			getToken();
			if(isIdentifier(FIELD_IDENTIFIER))
			{
				getToken();
				infipo();
			}
			else
				trataErro("Identificador de campo esperado");
		}
		else
			if(type == SMB_AT)
			{
				getToken();
				infipo();
			}
}

void Parser::factor()
{
	if (type == LIT_INT || type == LIT_FLOAT || type == KW_TRUE || type == KW_FALSE)
	{
		//ToDo 73
		getToken();
	}
	else if (type == KW_NIL)
	{
		//ToDo 110
		getToken();
	}
	else if (isIdentifier(VAR_IDENTIFIER))
	{
		//ToDo 170
		getToken();
		infipo();
		//ToDo 167
	}
	else if (isIdentifier(FUNCTION_IDENTIFIER))
	{
		//ToDo 77
		getToken();
		if (type == SMB_OPEN_PARENT)
		{
			do {
				getToken();
				expr();
				//ToDo 78
			} while (type == SMB_COMMA);
			if (type == SMB_CLOSE_PARENT)
			{
				//ToDo 79
				getToken();
			}
			else
			{
				trataErro("Símbolo , ou ) esperado");
			}
		}
		else
		{
			//ToDo 79
		}
	}
	else if (type == SMB_OPEN_PARENT)
	{
		getToken();
		expr();
		//ToDo 154
		if (type == SMB_CLOSE_PARENT)
			getToken();
		else
			trataErro("Símbolo ) esperado");
	}
	else if (type == KW_NOT)
	{
		getToken();
		factor();
		//ToDO 155
	}
	else if (type == SMB_OPEN_BRACKET)
	{
		getToken();
		if (type == SMB_CLOSE_BRACKET)
		{
			//ToDo 161
			getToken();
		}
		else 
		{
			do {
				expr();
				//ToDo 162
				if (type == SMB_DOUBLE_DOT)
				{
					getToken();
					expr();
					//ToDo 163
				}
			} while(verify_and_get(type == SMB_COMMA));
			if (type != SMB_CLOSE_BRACKET)
			{
				trataErro("Símbolo , ou ] esperado");
			}
		}
	}
	else if (isIdentifier(CONST_IDENTIFIER) || type == LIT_STRING)
		getToken();
	else
		trataErro("Literal, NIL, identificador, (, NOT ou [ esperado");
}

void Parser::term()
{
	do {
		factor();
		//ToDo 153
	} while( verify_and_get(type == OP_MULT || type == OP_DIV || type == KW_DIV || type == KW_MOD || type == KW_AND) );
}

void Parser::siexpr()
{
	if (type == OP_PLUS || type == OP_MINUS)
		getToken();
	term();
	//ToDo 152
	while(type == OP_PLUS || type == OP_MINUS || type == KW_OR)
	{
		getToken();
		term();
	}
}

void Parser::expr()
{
	siexpr();
	if (type == OP_EQUALS || type == OP_LOWER || type == OP_HIGHER || type == OP_DIFF || type == OP_HIGHER_EQUALS
		|| type == OP_LOWER_EQUALS || type == KW_IN)
	{
		getToken();
		siexpr();
		//ToDo 156
	}
}

void Parser::palist()
{
	if (type == SMB_OPEN_PARENT)
	{
		do {
			getToken();
			if (type == KW_PROCEDURE)
			{
				getToken();
				do {
					if (token.isIdentifier())
					{
						//registra token na tabela
						table.insert(pair<Token, TableRow>(token, TableRow(token, VAR_IDENTIFIER)));
						getToken();			
					}
					else
						trataErro("Identificador esperado");
				} while(type == SMB_COMMA);
			}
			else if (type == KW_FUNCTION || type == KW_VAR || token.isIdentifier())
			{
				if(type == KW_FUNCTION || type == KW_VAR)
					getToken();
				do {
					if (token.isIdentifier())
					{
						//registra token na tabela
						table.insert(pair<Token, TableRow>(token, TableRow(token, VAR_IDENTIFIER)));
						getToken();			
					}else
						trataErro("Identificador esperado");
				} while(verify_and_get (type == SMB_COMMA));
				if(type == SMB_COLON)
					getToken();
				else
					trataErro(": esperado");
				if(isIdentifier(TYPE_IDENTIFIER) || (type >= TYPE_INT && type <= TYPE_BOOLEAN))
					getToken();
				else
					trataErro("Identificador de tipo esperado");
			}
			else
				trataErro("Palavras-chave PROCEDURE, FUNCTION ou VAR, ou Identificador esperado");
			if (type == SMB_CLOSE_PARENT)
			{
				getToken();
				return;
			}
		} while(type == SMB_SEMICOLON);
		trataErro("Símbolo ; ou ) esperado");
	}
}

void Parser::statm()
{
    //number
    if (token.isNumber()) {
        getToken();
        if (type == SMB_COLON)
			getToken();
		else
            trataErro(": esperado");
    }
    //var identifier
    if (isIdentifier(VAR_IDENTIFIER)) {
        getToken();
        infipo();
        if (type == OP_ASSIGN) {
            getToken();
            expr();
        }
        else
            trataErro(":= esperado");
    }
    //function identifier
    else if (isIdentifier(FUNCTION_IDENTIFIER)) {
        getToken();
        if (type == OP_ASSIGN) {
            getToken();
            expr();
        }
        else
            trataErro(":= esperado");
    }
    //procedure identifier
    else if (isIdentifier(PROCEDURE_IDENTIFIER)) {
        getToken();
        if (type == SMB_OPEN_PARENT) {
            do {
                getToken();
                if (isIdentifier(PROCEDURE_IDENTIFIER))
                    getToken();
                else
                    expr();
            } while (type == SMB_COMMA);
            
            if (type == SMB_CLOSE_PARENT)
				getToken();
			else
                trataErro(") esperado");
        }
        else
        {
            //ToDo 79
        }
    }
    //begin
    else if (type == KW_BEGIN) {
        do {
            getToken();
            statm();
        } while (type == SMB_SEMICOLON);
        
        if (type == KW_END)
			getToken();
		else
            trataErro("end esperado");
    }
    //if
    else if (type == KW_IF) {
        getToken();
        expr();
        if (type == KW_THEN) {
            getToken();
            statm();
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
        if (type == KW_OF) {
            do {
                getToken();
                if (type == LIT_STRING || isIdentifier(CONST_IDENTIFIER) || token.isNumber())
                    getToken();
                else if (type == OP_PLUS || type == OP_MINUS) {
                    getToken();
                    if (isIdentifier(CONST_IDENTIFIER) || token.isNumber()) 
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
                    //; ou end esperado nesse ponto
                }
                else {
                    trataErro(", ou : esperado");
                    break;
                }
                
            } while (type == SMB_SEMICOLON);
            
            if (type == KW_END)
				getToken();
			else
                trataErro("end esperado");
        }
        else
            trataErro("of esperado");
    }
    //while
    else if (type == KW_WHILE) {
        getToken();
        expr();
        if (type == KW_DO) {
            getToken();
            statm();
        }
        else
            trataErro("'do' esperado");
    }
    //repeat
    else if (type == KW_REPEAT) {
        do {
            getToken();
            statm();
        } while (type == SMB_SEMICOLON);
        
        //until
        if (type == KW_UNTIL) {
            getToken();
            expr();
        }
        else
            trataErro("'until' esperado");
    }
    //for
    else if (type == KW_FOR) {
        getToken();
        if (isIdentifier(VAR_IDENTIFIER)) { 
            getToken();
            infipo();
            if (type == OP_ASSIGN) {
                getToken();
                expr();
                if (type == KW_TO || type == KW_DOWNTO) {
                    getToken();
                    expr();
                    if (type == KW_DO) {
                        getToken();
                        statm();
                    }
                    else
                        trataErro("'do' esperado");
                }
                else
                    trataErro("'to' ou 'downto' eesperado");
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
            if (isIdentifier(VAR_IDENTIFIER)) {
                getToken();
                infipo();
                //se este token for uma vírgula, continuará o laço
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
            trataErro("'do' esperado");
    }
    //goto
    else if (type == KW_GOTO) {
        getToken();
        if (type == LIT_INT)
			getToken();
		else
            trataErro("Número inteiro esperado");
    }
}

void Parser::read_type() 
{
    if (type == SMB_AT) 
    {
		getToken();
		if(isIdentifier(TYPE_IDENTIFIER) || (type >= TYPE_INT && type <= TYPE_BOOLEAN))
			getToken();
		else
			trataErro("Identificador de tipo esperado");
	}
	else
	{
        if (type == KW_PACKED)
            getToken();
        //ARRAY
        if (type == KW_ARRAY) {
            getToken();
            if (type == SMB_OPEN_BRACKET) {
                do {
                    getToken();
                    sitype();
                } while (type == SMB_COMMA);
                
                if (type == SMB_CLOSE_BRACKET) {
                    getToken();
                    if (type == KW_OF) {
                        getToken();
                        read_type();
                    }
                    else
                        trataErro("'of' esperado");
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
				getToken();
                read_type();
            }
            else
                trataErro("'of' esperado");
        }
        //SET
        else if (type == KW_SET) {
            getToken();
            if (type == KW_OF) {
				getToken();
                sitype();
            }
            else
                trataErro("'of' esperado");
        }
        //RECORD
        else if (type == KW_RECORD) {
            getToken();
            filist();
            if (type == KW_END)
				getToken();
			else
                trataErro("'end' esperado");
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
    if (type == KW_CONST) {
        getToken();
        if (token.isIdentifier()) {
            do {
				//registra token na tabela
				table.insert(pair<Token, TableRow>(token, TableRow(token, CONST_IDENTIFIER)));
                getToken();
                if (type == OP_EQUALS) {
                    getToken();
                    constant();
                    if (type == SMB_SEMICOLON) {
                        getToken();
                        //se for identificador: continuará o laço; caso contrário, continuará leitura do bloco
                    }
                    else
					{
						trataErro("; esperado");
						break;
					}
                }
                else {
                    trataErro("Operador = esperado");
                    break;
                }
            } while (token.isIdentifier());
        }
        else 
            trataErro("Identificador esperado");
    }
    //TYPE
    if (type == KW_TYPE) {
        getToken();
        if (token.isIdentifier()) {
            do {
				//registra token na tabela
				table.insert(pair<Token, TableRow>(token, TableRow(token, TYPE_IDENTIFIER)));
                getToken();
                if (type == OP_EQUALS) {
                    getToken();
                    read_type();
                    if (type == SMB_SEMICOLON) {
                        getToken();
                        //se for identificador: continuará o laço; caso contrário, continuará leitura do bloco
                    }
                    else
                    {
						trataErro("; esperado");
						break;
					}
                }
                else {
                    trataErro("Operador = esperado");
                    break;
                }
            } while (token.isIdentifier());
        }
        else 
            trataErro("Identificador esperado");
    }
    //VAR
    if (type == KW_VAR) {   
        getToken();
        if (token.isIdentifier()) {
            do {
				 //registra token na tabela
				table.insert(pair<Token, TableRow>(token, TableRow(token, VAR_IDENTIFIER)));
                getToken();
                if (type == SMB_COMMA)
                {
                    getToken();
                    if(!token.isIdentifier())
						trataErro("Identificador esperado");
                }
                else if (type == SMB_COLON) {
					getToken();
                    read_type();
                    if (type == SMB_SEMICOLON) {
                        getToken();
                        //se não for identificador, sairá do laço
                    }
                    else
						trataErro("; esperado");
                }
                else
					trataErro(": esperado");
            } while (token.isIdentifier());
        }
        else 
            trataErro("Identificador esperado");
    }
    do
    {
		//PROCEDURE
		if (type == KW_PROCEDURE) {
			getToken();
			if (token.isIdentifier()) {
				//registra token na tabela
				table.insert(pair<Token, TableRow>(token, TableRow(token, PROCEDURE_IDENTIFIER)));
				
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
		if (type == KW_FUNCTION) {
			getToken();
			if (token.isIdentifier()) {
				//registra token na tabela
				table.insert(pair<Token, TableRow>(token, TableRow(token, FUNCTION_IDENTIFIER)));
				getToken();
				palist();
				if (type == SMB_COLON) {
					getToken();
					if (token.isType()) {
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
	}while(type == KW_PROCEDURE || type == KW_FUNCTION);
    //BEGIN
    if (type == KW_BEGIN) {
        do {
            getToken();
            statm();
        } while (type == SMB_SEMICOLON);
        
        if (type == KW_END)
            getToken();
        else
            trataErro("End esperado");
            
        return;
    }
    else 
        trataErro("Label, Const, Type, Var, Procedure, Function ou Begin esperado");
}

void Parser::progrm()
{
    if (type == KW_PROGRAM) {
        getToken();
        if (token.isIdentifier()) {
            getToken();
            if (type == SMB_OPEN_PARENT) {
                do {
                    getToken();
                    if (token.isIdentifier()) {
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
    message += " (linha: " + to_string(token.getLine()) + ", coluna: " + to_string(token.getColumn()) + ")";
    errorQueue.push(message);
}
	
Parser::~Parser()
{
}

