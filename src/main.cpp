#include <stdio.h>
#include <iostream>
#include <string>
#include "LexicalAnalyzer.h"

using namespace std;

int main() {
    string fileName = "teste.txt";
	
    //TODO
    //std::cout << "Digite o caminho do arquivo a ser analisado: " << std::endl;
	//cin >> nomeArquivo;
    
    LexicalAnalyzer lexicalAnalyzer(fileName.c_str());
    lexicalAnalyzer.analyze();
    return 0;
}
