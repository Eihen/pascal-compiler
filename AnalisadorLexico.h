#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class AnalisadorLexico
{
public:
	AnalisadorLexico(const char* nomeArquivo);
	~AnalisadorLexico();
    void analisar();
private:
    void processaToken(string palavra);
    void exibirTabela();
    void gerarArquivo();
};

#endif // ANALISADORLEXICO_H
