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
        for (int i = 0, n = linha.length(); i < n; i++) {
            c = linha[i];

            if (Util::isDelimiter(c)) {
                processaToken(palavra); //processa o que já está na palavra
                palavra.clear();
                
                if (!Util::isSeparator(c)) { //se é um operador ou um símbolo, adiciona à lista de tokens
                    palavra.push_back(c);
                    processaToken(palavra);
                    palavra.clear();
                }
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
                
                processaToken(palavra);
                palavra.clear();
            }
            else
                palavra.push_back(c);
        }
    }
    
    //Teste - modificar arquivo
    //TODO printa lista
}

void AnalisadorLexico::exibirTabela()
{
	cout << endl;
	cout.width(32);
	cout.fill(' ');	
	cout << "Tabela de tokens" << endl;				//Título da tabela
	cout << "Lexema" << "\t" << "Token" << endl;	//Colunas
	for(list<Token>::iterator it = list.begin(); it != list.end(); it++)
	{
		cout << it->mValue << "\t";
		
		switch(it->mTipo)
		{
			case 0:
				cout << "Número com ponto flutuante";
			break;
			case 0:
				cout << "Número inteiro";
			break;
			case 0:
				cout << "Cadeia de caracteres";
			break;
			case 0:
				cout << "Identificador";
			break;
			case 0:
				cout << "Palavra chave";
			break;
		}
		cout << endl;
	}
}

AnalisadorLexico::~AnalisadorLexico()
{
}

