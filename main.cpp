#include <stdio.h>
#include <iostream>
#include <string>
#include "AnalisadorLexico.h"

using namespace std;

int main() {
    string nomeArquivo = "teste.txt";
	
    //TODO
    //std::cout << "Digite o caminho do arquivo a ser analisado: " << std::endl;
	//cin >> nomeArquivo;
    
    AnalisadorLexico analisadorLexico(nomeArquivo.c_str());
    analisadorLexico.analisar();
    return 0;
}