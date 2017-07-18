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
			LexicalAnalyzer(ifstream* file);
			LexicalAnalyzer(ifstream* file, TokenQueue* tokenQueue);
			~LexicalAnalyzer();
		private:
			list<Token> tokens;
			map<string, int> identifiers;
			int cont_ident;			//Conta os identificadores 
			TokenQueue* tokenQueue = NULL;

            void analyze(ifstream* file);
			void addToken(string word, int type, int line, int column);
			void showTable();
			void generateFile();
	};
}

#endif // LEXICALANALISER_H
