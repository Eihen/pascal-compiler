#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Token.h"

using namespace std;

class LexicalAnalyzer
{
public:
	LexicalAnalyzer(const char* nomeArquivo);
	~LexicalAnalyzer();
    void analyze();
private:
    ifstream file;
    list<Token> tokens;
    int cont_ident;			//Conta os identificadores 

	void addToken(string word, int type);
    void showTable();
    void generateFile();
};

#endif // LEXICALANALISER_H
