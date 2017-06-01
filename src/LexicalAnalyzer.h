#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include "Token.h"
#include "Helper.h"
#include "TokenQueue.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>

namespace std
{
	class LexicalAnalyzer
	{
		public:
			LexicalAnalyzer(const char* nomeArquivo);
			LexicalAnalyzer(const char* nomeArquivo, TokenQueue* tokenQueue);
			~LexicalAnalyzer();
			void analyze();
		private:
			ifstream file;
			list<Token> tokens;
			map<string, int> identifiers;
			int cont_ident;			//Conta os identificadores 
			TokenQueue* tokenQueue = NULL;

			void addToken(string word, int type, int line, int column);
			void showTable();
			void generateFile();
	};
}

#endif // LEXICALANALISER_H
