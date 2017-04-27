#include "LexicalAnalyzer.h"
#include "Helper.h"
#include "Token.h"
#include <stdio.h>

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(const char* fileName)
{
	file.open(fileName);
	cont_ident = 0;
}

void LexicalAnalyzer::addToken(string value, int type, int line, int column)
{
	Token token(value, type, line, column);
	tokens.push_back(token);
}

void LexicalAnalyzer::analyze()
{
	string line, word;
    char c, flag;
	int lineNumber = 0;
    while (getline(file, line)) {
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
					addToken(word, Helper::isKeyword(word) /* Verifica se é keyword, caso contrário é identificador */, lineNumber, i + 1);
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
						if (getline(file, line)) {
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
    
    //Imprime na tela e gera arquivo a partir da lista de tokens
    showTable();
    generateFile(); 
}

void LexicalAnalyzer::showTable()
{
	cout << endl;
	cout.width(48);
	cout.fill(' ');	
	cout << "Tabela de tokens" << endl << endl;        			  								//Título da tabela 
    cout << "Lexema" << "\t\t\t" << "Token" << "\t\t" << "Linha" << "\t" << "Coluna" << endl;  //Colunas 
	for(Token token : tokens)
    {
		cout.width(80);    //Separa linhas 
		cout << endl << cout.fill('-') << endl << token.getValue() << "\t\t\t";
		
		switch(token.getType())
		{
			case LIT_FLOAT:
				cout << "Número com ponto flutuante";
			break;
			case LIT_INT:
				cout << "Número inteiro";
			break;
			case LIT_STRING:
				cout << "Cadeia de caracteres";
			break;
			case ERR_CHAR:
				cout << "Caracter inválido";
			break;
			case ERR_SIZE:
				cout << "Identificador com muitos caracteres";
			break;
			case ERR_FORMAT:
				cout << "Cadeia inválida";
			break;
			case ERR_END_FILE:
				cout << "Fim inesperado de arquivo";
			break;
			default:
				if(token.getType() <= OP_DIV_ASSIGN)
					cout << "Operador " << token.getValue();
				else if(token.getType() <= KW_XOR)
					cout << "Palavra chave " << token.getValue();
				else if(token.getType() <= TYPE_BOOLEAN)
					cout << "Tipo " << token.getValue();
				else if(token.getType() <= SMB_SEMICOLON)
					cout << "Símbolo " << token.getValue();
				else
					cout << "Identificador " << token.getValue();
		}
		cout << "\t\t" << token.getLine() << "\t" << token.getColumn(); 
		cout << endl;
	}
}

void LexicalAnalyzer::generateFile()
{
	ofstream outFile;	
	outFile.open("saida.txt");
	outFile << endl; 
	outFile.width(48); 
	outFile.fill(' '); 
	outFile << "Tabela de tokens" << endl << endl;        										  //Título da tabela 
	outFile << "Lexema" << "\t\t\t" << "Token" << "\t\t" << "Linha" << "\t" << "Coluna" << endl;  //Colunas 

	for(Token token : tokens)
	{
		outFile.width(80);      //Separa linhas 
		outFile << endl << outFile.fill('-') << endl << token.getValue() << "\t\t\t"; 
		
		switch(token.getType())
		{
			case LIT_FLOAT:
				outFile << "Número com ponto flutuante";
			break;
			case LIT_INT:
				outFile << "Número inteiro";
			break;
			case LIT_STRING:
				outFile << "Cadeia de caracteres";
			break;
			case ERR_CHAR:
				outFile << "Caracter inválido";
			break;
			case ERR_SIZE:
				outFile << "Identificador com muitos caracteres";
			break;
			case ERR_FORMAT:
				outFile << "Cadeia inválida";
			break;
			default:
				if(token.getType() <= OP_DIV_ASSIGN)
					outFile << "Operador " << token.getValue();
				else if(token.getType() <= KW_XOR)
					outFile << "Palavra chave " << token.getValue();
				else if(token.getType() <= TYPE_BOOLEAN)
					outFile << "Tipo " << token.getValue();
				else if(token.getType() <= SMB_SEMICOLON)
					outFile << "Símbolo " << token.getValue();
				else
					outFile << "Identificador " << token.getValue();
		}
		outFile << "\t\t" << token.getLine() << "\t" << token.getColumn();
		outFile << endl;
	}
	outFile.close();
}

LexicalAnalyzer::~LexicalAnalyzer()
{
}

