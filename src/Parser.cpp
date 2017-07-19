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

    //warnings
    for (pair<string, VarEntry&> mapPair : varTable)
        if (!mapPair.second.isReferenced())
            cout << "Variavel " << mapPair.second.getIdentifier() << " nao utilizada." << endl;

    for (pair<string, ConstEntry&> mapPair : constTable)
        if (!mapPair.second.isReferenced())
            cout << "Constante " << mapPair.second.getIdentifier() << " nao utilizada." << endl;

    for (pair<string, TypeEntry&> mapPair : typeTable)
        if (!mapPair.second.isReferenced())
            cout << "Tipo " << mapPair.second.getIdentifier() << " nao utilizado." << endl;

    for (pair<string, FunctionEntry&> mapPair : functionTable)
        if (!mapPair.second.isReferenced())
            cout << "Função " << mapPair.second.getIdentifier() << " nao utilizada." << endl;

    for (pair<string, ProcedureEntry&> mapPair : procedureTable)
        if (!mapPair.second.isReferenced())
            cout << "Procedimento " << mapPair.second.getIdentifier() << " nao utilizado." << endl;
}

template<class T> bool Parser::isIdentifier(map<string, T> table, int scope)
{
    if (token.isIdentifier())
    {
        typename map<string, T>::iterator it = table.find(tokenHash(scope));
        if (it != table.end())
        {
            it->second.setReferenced(true);
            return true;
        }
    }
    return false;
}

template<class T> bool Parser::isIdentifier(map<string, T> table)
{
    return isIdentifier(table, currentScope) || isIdentifier(table, 0);
}

Type& Parser::currentTokenType()
{
	auto it = typeTable.find(tokenHash());
	if (it == typeTable.end())
		it = typeTable.find(tokenHash(0));
	TypeEntry typeEntry = it->second;
	return * new Type(typeEntry.getCode());
}

string Parser::tokenHash(int scope)
{
	return token.getValue() + "|" + to_string(scope);
}

string Parser::tokenHash()
{
	return tokenHash(currentScope);
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

string Parser::constant()
{
	if(type == LIT_STRING || type == LIT_INT || type == LIT_FLOAT || isIdentifier(constTable))
    {
        string constant = token.getValue();
        getToken();
        return constant;
    }
	else
		if(type == OP_PLUS || type == OP_MINUS)
		{
            string constant = token.getValue();
			getToken();
			if(type == LIT_INT || type == LIT_FLOAT || isIdentifier(constTable))
            {
                constant += token.getValue();
                getToken();
                return constant;
            }
			else
				trataErro("Literal esperado");
		}
		else
			trataErro("Operador + ou - esperado");
    return "";
}

Type& Parser::sitype()
{
	if(isIdentifier(typeTable))
    {
		Type& type = currentTokenType();
        getToken();
        return type;
    }
    else if (type >= TYPE_INT && type <= TYPE_BOOLEAN)
    {
        int sitype = type;
        getToken();
        return * new Type(sitype);
    }
	else {
        if(type == SMB_OPEN_PARENT) {
            list<string> identifiers;
            do {
                getToken();
                if (token.isIdentifier()) {
                    identifiers.push_back(token.getValue());
                    getToken();
                    if (type != SMB_COMMA && type != SMB_CLOSE_PARENT)
                        trataErro("Vírgula ou parenteses esperado");
                }
                else
                    trataErro("Identificador esperado");
            } while (type == SMB_COMMA);
            //token nesse ponto é )
            getToken();
            return * new FieldListType(identifiers);
        }
		else {
            string low = constant();
            if (type == SMB_DOUBLE_DOT) {
                getToken();
                string high = constant();
                return * new DimensionType(low, high);
            }
            else
                trataErro("Delimitador .. esperado");
        }
    }
    return * new Type();
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
			if(isIdentifier(typeTable) || (type >= TYPE_INT && type <= TYPE_BOOLEAN))
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
		if(isIdentifier(typeTable) || (type >= TYPE_INT && type <= TYPE_BOOLEAN))
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
	if(type == LIT_STRING || isIdentifier(constTable) || type == LIT_INT || type == LIT_FLOAT)
	{
		getToken();
		aux_filist_p3();
	}
	else
		if(type == OP_PLUS || type == OP_MINUS)
		{
			getToken();
			if(isIdentifier(constTable) || type == LIT_INT || type == LIT_FLOAT)
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
        fieldTable.insert(pair<string, FieldEntry&>(tokenHash(), * new FieldEntry(token)));
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
			if(isIdentifier(fieldTable))
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
	else if (isIdentifier(varTable))
	{
		//ToDo 170
		getToken();
		infipo();
		//ToDo 167
	}
	else if (isIdentifier(functionTable, 0))
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
	else if (isIdentifier(constTable) || type == LIT_STRING)
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

list<SymbolTableEntry> Parser::palist()
{
	list<SymbolTableEntry> entries;
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
						ProcedureEntry& procedureEntry = * new ProcedureEntry(token, currentScope);
						entries.push_back(procedureEntry);
						//registra token na tabela
						procedureTable.insert(pair<string, ProcedureEntry&>(tokenHash(), procedureEntry));
						getToken();
					}
					else
						trataErro("Identificador esperado");
				} while(type == SMB_COMMA);
			}
			else if (type == KW_FUNCTION || type == KW_VAR || token.isIdentifier())
			{
				list<VarEntry> vars;
				if(type == KW_FUNCTION || type == KW_VAR)
					getToken();
				do {
					if (token.isIdentifier())
					{
						VarEntry& varEntry = * new VarEntry(token, currentScope);
						vars.push_back(varEntry);
						//registra token na tabela
						varTable.insert(pair<string, VarEntry&>(tokenHash(), varEntry));
						getToken();
					}else
						trataErro("Identificador esperado");
				} while(verify_and_get (type == SMB_COMMA));
				if(type == SMB_COLON)
					getToken();
				else
					trataErro(": esperado");
				if(isIdentifier(typeTable))
				{
					Type& type = currentTokenType();
					for (VarEntry var : vars)
					{
						var.setType(type);
						entries.push_back(var);
					}
					getToken();
				}
                else if (type >= TYPE_INT && type <= TYPE_BOOLEAN)
                {
                    Type& type = * new Type(this->type);
                    for (VarEntry var : vars)
                    {
                        var.setType(type);
                        entries.push_back(var);
                    }
                    getToken();
                }
				else
					trataErro("Identificador de tipo esperado");
			}
			else
				trataErro("Palavras-chave PROCEDURE, FUNCTION ou VAR, ou Identificador esperado");
			if (type == SMB_CLOSE_PARENT)
			{
				getToken();
				return entries;
			}
		} while(type == SMB_SEMICOLON);
		trataErro("Símbolo ; ou ) esperado");
	}
	return entries;
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
    if (isIdentifier(varTable)) {
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
    else if (isIdentifier(functionTable, 0)) {
        getToken();
        if (type == OP_ASSIGN) {
            getToken();
            expr();
        }
        else
            trataErro(":= esperado");
    }
    //procedure identifier
    else if (isIdentifier(procedureTable, 0)) {
        getToken();
        if (type == SMB_OPEN_PARENT) {
            do {
                getToken();
                if (isIdentifier(procedureTable, 0))
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
                if (type == LIT_STRING || isIdentifier(constTable) || token.isNumber())
                    getToken();
                else if (type == OP_PLUS || type == OP_MINUS) {
                    getToken();
                    if (isIdentifier(constTable) || token.isNumber())
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
        if (isIdentifier(varTable)) {
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
            if (isIdentifier(varTable)) {
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

Type& Parser::read_type()
{
    if (type == SMB_AT)
    {
		getToken();
		if(isIdentifier(typeTable))
        {
			Type& type = currentTokenType();
            getToken();
            return type;
        }
        else if (type >= TYPE_INT && type <= TYPE_BOOLEAN)
        {
            int sitype = type;
            getToken();
            return * new Type(sitype);
        }
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
                list<DimensionType> dimensions;
                do {
                    getToken();
                    Type& siType = sitype();
                    if(DimensionType* dimension = dynamic_cast<DimensionType*>(&siType))
                        dimensions.push_back(*dimension);
                } while (type == SMB_COMMA);

                if (type == SMB_CLOSE_BRACKET) {
                    getToken();
                    if (type == KW_OF) {
                        getToken();
                        Type& ofType = read_type();
                        return * new ArrayType(dimensions);
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
                Type& fileType = read_type();
                if (fileType.getCode())
                    return * new OfType(Type::TYPE_FILE, fileType);
            }
            else
                trataErro("'of' esperado");
        }
        //SET
        else if (type == KW_SET) {
            getToken();
            if (type == KW_OF) {
				getToken();
                Type& setType = sitype();
                if (setType.getCode())
                    return * new OfType(Type::TYPE_SET, setType);
            }
            else
                trataErro("'of' esperado");
        }
        //RECORD
        else if (type == KW_RECORD) {
            //TODO type record com lista de variaveis
            getToken();
            filist();
            if (type == KW_END)
				getToken();
			else
                trataErro("'end' esperado");
        }
        else
            return sitype();
    }
    return * new Type();
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
				constTable.insert(pair<string, ConstEntry&>(tokenHash(), * new ConstEntry(token, currentScope)));
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
				typeTable.insert(pair<string, TypeEntry&>(tokenHash(), * new TypeEntry(token, currentScope)));
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
            list<VarEntry> variables;
            Type& varType = * new Type();
            do {
				 //registra token na tabela
				VarEntry& entry = * new VarEntry(token, currentScope);
                variables.push_back(entry);
				varTable.insert(pair<string, VarEntry&>(tokenHash(), entry));
                getToken();
                if (type == SMB_COMMA)
                {
                    getToken();
                    if(!token.isIdentifier())
						trataErro("Identificador esperado");
                }
                else if (type == SMB_COLON) {
					getToken();
                    varType = read_type();
                    if (type == SMB_SEMICOLON) {
                        getToken();

                        //define o tipo das variáveis listadas
                        for (VarEntry varEntry : variables)
                            varEntry.setType(varType);

                        variables.clear();
                        //se não for identificador, sairá do laço
                    }
                    else
						trataErro("; esperado");
                }
                else
					trataErro(": ou , esperado");
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
                currentScope = previousScope + 1;
				//registra token na tabela
				ProcedureEntry& procedureEntry = * new ProcedureEntry(token, currentScope);
				procedureTable.insert(pair<string, ProcedureEntry&>(tokenHash(0), procedureEntry));

				getToken();
				list<SymbolTableEntry> params = palist();
				procedureEntry.setParams(params);
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
                previousScope = currentScope;
                currentScope = 0;
			}
			else
				trataErro("Identificador esperado");
		}
		//FUNCTION
		if (type == KW_FUNCTION) {
			getToken();
			if (token.isIdentifier()) {
                currentScope = previousScope + 1;
				//registra token na tabela
				FunctionEntry& functionEntry = * new FunctionEntry(token, currentScope);
				functionTable.insert(pair<string, FunctionEntry&>(tokenHash(0), functionEntry));
				getToken();
				list<SymbolTableEntry> params = palist();
				functionEntry.setParams(params);
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
            previousScope = currentScope;
            currentScope = 0;
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