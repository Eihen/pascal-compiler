#include "AnalisadorLexico.h"
#include "Util.h"
#include "Token.h"
#include "StringToken.h"
#include "NumberToken.h"
#include "OperatorToken.h"
#include "SymbolToken.h"
#include <stdio.h>

using namespace std;

AnalisadorLexico::AnalisadorLexico(const char* nomeArquivo)
{
	file.open(nomeArquivo);
	cont_ident = 0;
}

void AnalisadorLexico::processaTokenNumerico(string palavra) {
    NumberToken token(palavra);
    tokens.push_back(palavra);
}

void AnalisadorLexico::processaTokenSimbolo(string palavra) {
    SymbolToken token(palavra);
    tokens.push_back(token);
}

void AnalisadorLexico::processaTokenString(string palavra) {
    StringToken token(palavra);
    tokens.push_back(token);
}

void AnalisadorLexico::processaTokenOperador(string palavra) {
    OperatorToken token(palavra);
    tokens.push_back(token);
}

void AnalisadorLexico::analisar()
{
	string linha, palavra;
    char c;
    while (getline(file, linha)) {
		linha += '\n';
        for (int i = 0, n = linha.length(); i < n; i++) {
            c = linha[i];
            
            //leitura de número
            if (NumberToken::isNumber(c)) {
                palavra = c;
                
                //lê N dígitos
                for (i = i + 1; i < n; i++) {
                    c = linha[i];
                    if (NumberToken::isNumber(c))
                        palavra += c;
                    //leitura ponto flutuante
                    else if (c == '.') {
                        palavra += c;
                        for (i = i + 1; i < n; i++) {
                            //lê N dígitos; ao encontrar delimitador, finaliza token
                            c = linha[i];
                            if (NumberToken::isNumber(c))
                                palavra += c;
                            //TODO verificar aqui se é outro "." e fazer algo a respeito
                            else if (Util::isDelimiter(c)) {
                                processaTokenNumerico(palavra);
                                i--;
                                break;
                            }
                            //TODO else erro léxico
                        }
                        break;
                    }
                    //número inteiro encontrado
                    else if (Util::isDelimiter(c)) {
                        processaTokenNumerico(palavra);
                        i--;
                        break;
                    }
                    //TODO else erro léxico
                }
                    
            }
            //leitura de identificador/palavra reservada
			else if (StringToken::isLetter(c)) {
                palavra = c;
                for (i = i + 1; i < n; i++) {
                    c = linha[i];
                    if (NumberToken::isNumber(c) || StringToken::isLetter(c))
                        palavra += c;
                    else if (Util::isDelimiter(c)){
                        processaTokenString(palavra);
                        i--;
                        break;
                    }
                    //TODO else erro léxico
                }
            }
            else if (SymbolToken::isSymbol(c)) {
                //processa símbolo
                palavra = c;
                processaTokenSimbolo(palavra);
            }
            else if (OperatorToken::isOperator(c)) {
                palavra = c;
                
                //tratamento de símbolos de 2 caracteres
                if (OperatorToken::operadorPrefixo(c) && i + 1 < n) {
                    char proximo = linha[i + 1];
                    if ((c == '<' && (proximo == '>' || proximo == '<' || proximo == '=')) || // <> ou << ou <=
                        (c == '>' && (proximo == '>' || proximo == '=')) ||
                        (c == ':' && proximo == '=')) { // >> ou >=
                        palavra += proximo; 
                        i++;
                    }
                }
                
                //processa operador
                processaTokenOperador(palavra);
            }
            else if (c == '\'') {
                //lê string
                palavra = c;
                for (i = i + 1; i < n; i++) {
                    c = linha[i];
                    if (c == '\'') {
                        palavra += c;
                        if (i + 1 < n) {
                            c = linha[++i];
                            //verifica se o apóstrofo foi escapado
                            if (c == '\'') {
                                palavra += c;
                            }
                            else if (Util::isDelimiter(c)) {
                                processaTokenString(palavra);
                                i--;
                                break;
                            }
                            //TODO else erro léxico
                        }
                        //TODO else erro léxico
                    }
                    else
                        palavra += c;
                }
            }
        }
    }
    
    //Teste - modificar arquivo
    exibirTabela();
    gerarArquivo(); 
}

void AnalisadorLexico::exibirTabela()
{
	cout << endl;
	cout.width(48);
	cout.fill(' ');	
	cout << "Tabela de tokens" << endl << endl;        //Título da tabela 
    cout << "Lexema" << "\t\t\t\t\t" << "Token" << endl;  //Colunas 
	for(Token token : tokens)
    {
		cout.width(80);    //Separa linhas 
		cout << endl << cout.fill('-') << endl << token.getValue() << "\t\t\t\t\t";
		
		switch(token.getTipo())
		{
			case NumberToken::TIPO_FLOAT:
				cout << "Número com ponto flutuante";
			break;
			case NumberToken::TIPO_INT:
				cout << "Número inteiro";
			break;
			case StringToken::TIPO_STRING:
				cout << "Cadeia de caracteres";
			break;
			case StringToken::TIPO_IDENTIFICADOR:
				cout << "Identificador";
			break;
			case StringToken::TIPO_KEYWORD:
				cout << "Palavra chave";
			break;
			case OperatorToken::TIPO_OPERADOR:
				cout << "Operador";
			break;
			case SymbolToken::TIPO_SIMBOLO:
				cout << "Símbolo";
			break;
		}
		cout << endl;
	}
}

void AnalisadorLexico::gerarArquivo()
{
	ofstream outFile;
	outFile.open("saida.txt");
	outFile << endl; 
	outFile.width(48); 
	outFile.fill(' '); 
	outFile << "Tabela de tokens" << endl << endl;        //Título da tabela 
	outFile << "Lexema" << "\t\t\t\t\t" << "Token" << endl;    //Colunas 

	for(Token token : tokens)
	{
		outFile.width(80);      //Separa linhas 
		outFile << endl << outFile.fill('-') << endl << token.getValue() << "\t\t\t\t\t"; 
		
		switch(token.getTipo())
		{
			case NumberToken::TIPO_FLOAT:
				outFile << "Número com ponto flutuante";
			break;
			case NumberToken::TIPO_INT:
				outFile << "Número inteiro";
			break;
			case StringToken::TIPO_STRING:
				outFile << "Cadeia de caracteres";
			break;
			case StringToken::TIPO_IDENTIFICADOR:
				outFile << "Identificador";
			break;
			case StringToken::TIPO_KEYWORD:
				outFile << "Palavra chave";
				break;
			case OperatorToken::TIPO_OPERADOR:
				outFile << "Operador";
			break;
			case SymbolToken::TIPO_SIMBOLO:
				outFile << "Símbolo";
			break;
		}
		outFile << endl;
	}
	outFile.close();
}

AnalisadorLexico::~AnalisadorLexico()
{
}

