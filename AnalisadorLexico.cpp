#include "AnalisadorLexico.h"

ifstream file;

AnalisadorLexico::AnalisadorLexico(const char* nomeArquivo)
{
	file.open(nomeArquivo);
    analisar();
}

void analisar()
{
	cout << 25;
}

AnalisadorLexico::~AnalisadorLexico()
{
}

