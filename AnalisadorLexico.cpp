#include "AnalisadorLexico.h"

ifstream file;

AnalisadorLexico::AnalisadorLexico(const char* nomeArquivo)
{
	file.open(nomeArquivo);
}

void AnalisadorLexico::analisar()
{
	
}

AnalisadorLexico::~AnalisadorLexico()
{
}

