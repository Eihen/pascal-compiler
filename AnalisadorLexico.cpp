#include "AnalisadorLexico.h"
#include "Util.h"
#include "Token.h"
#include <stdio.h>
#include <list>

using namespace std;

ifstream file;
list<Token> tokens;

AnalisadorLexico::AnalisadorLexico(const char* nomeArquivo)
{
	file.open(nomeArquivo);
}

void AnalisadorLexico::processaToken(string palavra)
{
    if (palavra.length() > 0) {
        Token token(palavra);
        tokens.push_back(token);
    }
}

void AnalisadorLexico::analisar()
{
	string linha, palavra;
    char c;
    while (getline(file, linha)) {
		linha += '\n';
        for (int i = 0, n = linha.length(); i < n; i++) {
            c = linha[i];
			
            if (Util::isSeparator(c)) {
                processaToken(palavra);
                palavra.clear();
            }
            else if (Util::isSymbol(c)) {
                //processa palavra anterior 
                processaToken(palavra); 
                palavra.clear();
                
                //processa símbolo
                palavra.push_back(c);
                processaToken(palavra);
                palavra.clear();
            }
            else if (Util::isOperator(c)) {
                //processa palavra anterior
                processaToken(palavra); 
                palavra.clear();
                
                palavra.push_back(c);
                
                //tratamento de símbolos de 2 caracteres
                if (Util::operadorPrefixo(c) && i + 1 < n) {
                    char proximo = linha[i + 1];
                    if ((c == '<' && (proximo == '>' || proximo == '<' || proximo == '=')) || // <> ou << ou <=
                        (c == '>' && (proximo == '>' || proximo == '=')) ||
                        (c == ':' && proximo == '=')) { // >> ou >=
                        palavra.push_back(proximo); 
                        i++;
                    }
                }
                
                //processa símbolo
                processaToken(palavra);
                palavra.clear();
            }
            else if (c == '\'') {
                processaToken(palavra); //processa o que já estava lido, já que uma aspas inicial também é um separador
                palavra.clear();
                
                //lê string
                palavra.push_back(c);
                do {
                    c = linha[i++]; //TODO e se o i não estiver no vetor? erro na análise ou bola pra frente?
                    palavra.push_back(c);
                } while (c != '\'');
            }
            else
                palavra.push_back(c);
        }
    }
    
    //Teste - modificar arquivo
    exibirTabela();
}

void AnalisadorLexico::exibirTabela()
{
	cout << endl;
	cout.width(32);
	cout.fill(' ');	
	cout << "Tabela de tokens" << endl;				//Título da tabela
	cout << "Lexema" << "\t\t" << "Token" << endl;	//Colunas
	for(Token token : tokens)
    {
		cout << token.getValue() << "\t\t";
		
		switch(token.getTipo())
		{
			case Token::TIPO_FLOAT:
				cout << "Número com ponto flutuante";
			break;
			case Token::TIPO_INT:
				cout << "Número inteiro";
			break;
			case Token::TIPO_STRING:
				cout << "Cadeia de caracteres";
			break;
			case Token::TIPO_IDENTIFICADOR:
				cout << "Identificador";
			break;
			case Token::TIPO_KEYWORD:
				cout << "Palavra chave";
			break;
			case Token::TIPO_OPERADOR:
				cout << "Operador";
			break;
			case Token::TIPO_SYMBOL:
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
	outFile << "Tabela de tokens" << endl;				//Título da tabela
	outFile << "Lexema" << "\t\t" << "Token" << endl;		//Colunas
	for(Token token : tokens)
	{
		outFile << token.getValue() << "\t\t";
		
		switch(token.getTipo())
		{
			case Token::TIPO_FLOAT:
				outFile << "Número com ponto flutuante";
			break;
			case Token::TIPO_INT:
				outFile << "Número inteiro";
			break;
			case Token::TIPO_STRING:
				outFile << "Cadeia de caracteres";
			break;
			case Token::TIPO_IDENTIFICADOR:
				outFile << "Identificador";
			break;
			case Token::TIPO_KEYWORD:
				outFile << "Palavra chave";
				break;
			case Token::TIPO_OPERADOR:
				outFile << "Operador";
			break;
			case Token::TIPO_SYMBOL:
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

