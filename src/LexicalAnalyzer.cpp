#include "LexicalAnalyzer.h"

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream* file)
{
	cont_ident = IDENTIFIER;
    analyze(file);
}

LexicalAnalyzer::LexicalAnalyzer(ifstream* file, TokenQueue* _tokenQueue)
{
	cont_ident = IDENTIFIER;
	tokenQueue = _tokenQueue;
    analyze(file);
}

void LexicalAnalyzer::addToken(string value, int type, int line, int column)
{
	Token token(value, type, line, column - value.length());			//Subtrai o tamanho da palavra para indicar a coluna da primeira letra
	
	if (tokenQueue != NULL)
	{
		tokenQueue->enqueue(token);
	}
	tokens.push_back(token);
}

void LexicalAnalyzer::analyze(ifstream* file)
{
	string line, word;
    char c, flag;
	int lineNumber = 0;
    while (getline(*file, line)) {
		line += '\n';
		lineNumber++;
        for (int i = 0, n = line.length(); i < n; i++) {
            c = line[i];
            
            //leitura de número
            if (Helper::isNumber(c)) {
                word = c;
				flag = -1;
                
                //lê N dígitos
                for (i = i + 1; i < n; i++) {
                    c = line[i];
					
                    if (Helper::isNumber(c))
                        word += c;
						
                    //leitura ponto flutuante
                    else if (c == '.') {
						flag++;
                        word += c;
                    }
					
                    //número inteiro encontrado
                    else if (Helper::isDelimiter(c)) {
						i--;
						break;
                    }
					else
					{
						word += c;
						flag += 2; //Garante que um erro de formato será gerado
					}
                }
				if (flag < 0) //int
				{
					flag = LIT_INT;
				}
				else if (flag == 0) //float
				{
					flag = LIT_FLOAT;
				}
				else { //erro
					flag = ERR_FORMAT;
				}
				addToken(word, flag, lineNumber, i + 1);
            }
            //leitura de identificador/palavra reservada
			else if (Helper::isLetter(c)) { //começa com letra
                word = c;
				flag = 0;
                for (i = i + 1; i < n; i++) {
                    c = line[i];
                    if (Helper::isNumber(c) || Helper::isLetter(c)) //composto por número, letra ou _
                        word += c;
                    else if (Helper::isDelimiter(c)) { //delimitador encontrado, token finalizada
                        i--;
                        break;
                    }
					else //caracter inválido
					{
						word += c;
						flag = 1;
					}
                }
				if (flag) //erro
				{
					addToken(word, ERR_FORMAT, lineNumber, i + 1);
				}
				else
				{
					int type = Helper::isKeyword(word); // Verifica se é keyword, caso contrário é identificador
					if (type == IDENTIFIER)
					{
						word = Helper::toUpper(word);
						map<string,int>::iterator it = identifiers.find(word);
						if (it == identifiers.end())
						{
							type = cont_ident++;
							identifiers.insert(pair<string, int>(word, type));
						}
						else
						{
							type = it->second;
						}
					}
					addToken(word, type, lineNumber, i + 1);
				}
            }
            else if (c == '\'') { //Inicia com apostrofo, lê string
                word = c;
				flag = 0;

                for (i = i + 1; i < n; i++) {
                    c = line[i];
					
                    if (c == '\'') { //apostrofo pode ser finalizador ou precisa ser escapado
                        word += c;
						
                        if (i + 1 < n) {
                            c = line[++i];
                            //verifica se o apóstrofo foi escapado
                            if (c == '\'') {
                                word += c;
                            }
                            else if (Helper::isDelimiter(c)) { //delimitador encontrado, token finalizada
								i--;
                                break;
                            }
							else //apostrofo não escapado, erro
							{
								flag = 1;
							}
                        }
						else //fim da linha sem finalizador, erro
						{
							flag = 1;
						}
                    }
                    else
                        word += c;
                }
				if (flag) //erro
				{
					addToken(word, ERR_FORMAT, lineNumber, i + 1);
				}
				else //string literal
				{
					addToken(word, LIT_STRING, lineNumber, i + 1);
				}
            }
			// Comentários
			else if (c == '/' && (i + 1 < n && (line[i + 1] == '/' || line [i + 1] == '*'))) {
				if (line[i + 1] == '/')
					break; //ignora toda a linha
				// /*
				for (i = i + 2; i < n; i++) {
					//finalizador do comentário
					if (line[i] == '*') {
						int next = i + 1;
						if (next < n && line[next] == '/') {
							i = next;
							break;
						}
					}
					
					if (i == (n - 1)) //verifica se linha já foi finalizada e lê a próxima
					{
						if (getline(*file, line)) {
							i = 0;
							n = line.length();
						}
						else {
							addToken("/*", ERR_END_FILE, lineNumber, i + 1); //Comentário não finalizado, fim inesperado de arquivo
							break;
						}
					}
				}
			}
            else if (!Helper::isSeparator(c)) { //Se não for separador, verifica simbolo ou operador
				word = c;
				if ((i + 1) < n && Helper::isSymbolPrefix(c)) //verifica se pode ser simbolo ou operador com dois caracteres
				{
					word += line[i+1];
					if ((flag = Helper::isSymbol(word)) == ERR_CHAR) //Verifica se o simbolo ou operador com dois caracteres é inválido
					{
						word = c;
						flag = Helper::isSymbol(word); //Verifica o simbolo ou operador com só um caracter
					}
					else
					{
						i++; //Simbolo ou operador com dois caracteres é válido, então o próximo caracter já foi lido
					}
				}
				else
				{
					flag = Helper::isSymbol(word); //Não pode ser simbolo ou operador com dois caracteres, verifica apenas com um
				}
				addToken(word, flag, lineNumber, i + 1);
            }
        }
    }
	
	//Sinaliza que não há mais tokens a serem adicionadas
	if (tokenQueue != NULL)
	{
		(*tokenQueue).finish();
	}
	
    //Imprime na tela e gera arquivo a partir da lista de tokens
    //showTable();
    generateFile(); 
}

void LexicalAnalyzer::showTable()
{
	//Título------------------------------------------------------------
	cout.fill(' ');	  cout.width(32);	cout << ' ';
	cout << "Tabela de tokens" << endl << endl;        			  								 
	//------------------------------------------------------------------
	//Colunas-----------------------------------------------------------
    cout << "Lexema";
    cout.fill(' ');    cout.width(32);  cout << "| ";					//Espaço entre "Lexema e Token"
    cout << "Token";
    cout.fill(' ');	   cout.width(23);	cout << "| ";  					//Espaço entre "Token" e "Linha"
    cout << "Linha" << " | " << "Coluna" << endl;
    //------------------------------------------------------------------  							
	for(Token token : tokens)
    { 
		cout.fill('-');		cout.width(80);		cout << '-';								//Separa linhas  								  
		cout << endl << token.getValue();													//Lexema
		cout.fill(' ');     cout.width(38 - token.getValue().length());		cout << "| ";	//Tabulação
		
		switch(token.getType())
		{
			case LIT_FLOAT:
				cout << "Número com ponto flutuante";
				cout.width(2);
			break;
			case LIT_INT:
				cout << "Número inteiro";
				cout.width(14);
			break;
			case LIT_STRING:
				cout << "Cadeia de caracteres";
				cout.width(8);
			break;
			case ERR_CHAR:
				cout << "Caracter inválido";
				cout.width(11);
			break;
			case ERR_SIZE:
				cout << "Ident. com muitos carac.";
				cout.width(4);
			break;
			case ERR_FORMAT:
				cout << "Cadeia inválida";
				cout.width(13);
			break;
			case ERR_END_FILE:
				cout << "Fim inesperado de arquivo";
				cout.width(3);
			break;
			default:
				if(token.getType() <= OP_DIV_ASSIGN)
				{
					cout << "Operador " << token.getValue();
					cout.width(19 - token.getValue().length());
				}
				else if(token.getType() <= KW_XOR)
				{
					cout << "Palavra chave " << token.getValue();
					cout.width(14 - token.getValue().length());
				}
				else if(token.getType() <= TYPE_BOOLEAN)
				{
					cout << "Tipo " << token.getValue();
					cout.width(23 - token.getValue().length());
				}
				else if(token.getType() <= SMB_SEMICOLON)
				{
					cout << "Símbolo " << token.getValue();
					cout.width(20 - token.getValue().length());
				}
				else
				{
					cout << "Identificador " << token.getType() - IDENTIFIER + 1;			//Subtrai o valor base para determinar o número do identificador
					cout.width(14 - to_string(token.getType() - IDENTIFIER + 1).length());  //Subtrai o valor base para determinar o número do identificador
				}
		}
		cout << "| ";													//Tabulação
		cout << token.getLine();
		cout.width(8 - to_string(token.getLine()).length());
		cout << "| ";													//Tabulação
		cout << token.getColumn() << endl;
		//Linha vertical da tabela
		cout.width(38);
		cout << "| ";
		cout.width(28);
		cout << "| ";
		cout.width(8);
		cout << "| " << endl;
		//-------------------------
	}
}

void LexicalAnalyzer::generateFile()
{
	ofstream outFile;	
	outFile.open("saida.txt");
	//Título------------------------------------------------------------
	outFile.fill(' ');	  outFile.width(32);	outFile << ' ';
	outFile << "Tabela de tokens" << endl << endl;        			  								 
	//------------------------------------------------------------------
	//Colunas-----------------------------------------------------------
    outFile << "Lexema";
    outFile.fill(' ');    outFile.width(32);  outFile << "| ";			//Espaço entre "Lexema e Token"
    outFile << "Token";
    outFile.fill(' ');	  outFile.width(23);  outFile << "| ";  		//Espaço entre "Token" e "Linha"
    outFile << "Linha" << " | " << "Coluna" << endl;
    //------------------------------------------------------------------  							
	for(Token token : tokens)
    { 
		outFile.fill('-'); outFile.width(80);	 outFile << '-';		//Separa linhas  								  
		outFile << endl << token.getValue();													//Lexema
		outFile.fill(' '); outFile.width(38 - token.getValue().length());	outFile << "| ";	//Tabulação
		
		switch(token.getType())
		{
			case LIT_FLOAT:
				outFile << "Número com ponto flutuante";
				outFile.width(2);
			break;
			case LIT_INT:
				outFile << "Número inteiro";
				outFile.width(14);
			break;
			case LIT_STRING:
				outFile << "Cadeia de caracteres";
				outFile.width(8);
			break;
			case ERR_CHAR:
				outFile << "Caracter inválido";
				outFile.width(11);
			break;
			case ERR_SIZE:
				outFile << "Ident. com muitos carac.";
				outFile.width(4);
			break;
			case ERR_FORMAT:
				outFile << "Cadeia inválida";
				outFile.width(13);
			break;
			case ERR_END_FILE:
				outFile << "Fim inesperado de arquivo";
				outFile.width(3);
			break;
			default:
				if(token.getType() <= OP_DIV_ASSIGN)
				{
					outFile << "Operador " << token.getValue();
					outFile.width(19 - token.getValue().length());
				}
				else if(token.getType() <= KW_XOR)
				{
					outFile << "Palavra chave " << token.getValue();
					outFile.width(14 - token.getValue().length());
				}
				else if(token.getType() <= TYPE_BOOLEAN)
				{
					outFile << "Tipo " << token.getValue();
					outFile.width(23 - token.getValue().length());
				}
				else if(token.getType() <= SMB_SEMICOLON)
				{
					outFile << "Símbolo " << token.getValue();
					outFile.width(20 - token.getValue().length());
				}
				else
				{
					outFile << "Identificador " << token.getType() - IDENTIFIER + 1;			//Subtrai o valor base para determinar o número do identificador
					outFile.width(14 - to_string(token.getType() - IDENTIFIER + 1).length());  //Subtrai o valor base para determinar o número do identificador
				}
		}
		outFile << "| ";												//Tabulação
		outFile << token.getLine();
		outFile.width(8 - to_string(token.getLine()).length());
		outFile << "| ";												//Tabulação
		outFile << token.getColumn() << endl;
		//Linha vertical da tabela
		outFile.width(38);
		outFile << "| ";
		outFile.width(28);
		outFile << "| ";
		outFile.width(8);
		outFile << "| " << endl;
		//-------------------------
	}
	outFile.close();
}

LexicalAnalyzer::~LexicalAnalyzer()
{
}

