#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Token.h"

using namespace std;

class AnalisadorLexico
{
public:
	AnalisadorLexico(const char* nomeArquivo);
	~AnalisadorLexico();
    void analisar();
private:
    ifstream file;
    list<Token> tokens;

    void processaTokenNumerico(string palavra);
    void processaTokenSimbolo(string palavra);
    void processaTokenString(string palavra);
    void processaTokenOperador(string palavra);
    void exibirTabela();
    void gerarArquivo();
};

#endif // ANALISADORLEXICO_H
