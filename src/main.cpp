#include <cstdio>
#include <iostream>
#include <string>
#include <thread>
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "TokenQueue.h"

using namespace std;

TokenQueue tokenQueue;

void lexicalCallFromThread(const char* fileName)
{
	LexicalAnalyzer lexicalAnalyzer(fileName, &tokenQueue);
	lexicalAnalyzer.analyze();
}

void parserCallFromThread()
{
	Parser parser(&tokenQueue);
}

int main() {
	string fileName = "teste.txt";
	
	//TODO
	//cout << "Digite o caminho do arquivo a ser analisado: " << endl;
	//cin >> nomeArquivo;
	thread lexicalThread(lexicalCallFromThread, fileName.c_str());
	thread parserThread(parserCallFromThread);
	
	lexicalThread.join();
	parserThread.join();
	return 0;
}

