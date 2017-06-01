#include <cstdio>
#include <iostream>
#include <string>
#include "LexicalAnalyzer.h"
#include "TokenQueue.h"
#include "Token.h"
#include <thread>

using namespace std;

TokenQueue tokenQueue;

void lexicalCallFromThread(const char* fileName)
{
	LexicalAnalyzer lexicalAnalyzer(fileName, &tokenQueue);
	lexicalAnalyzer.analyze();
}

void parserCallFromThread()
{
	
}

int main() {
	string fileName = "teste.txt";
	
	//TODO
	//std::cout << "Digite o caminho do arquivo a ser analisado: " << std::endl;
	//cin >> nomeArquivo;
	std::thread lexicalThread(lexicalCallFromThread, fileName.c_str());
	std::thread parserThread(parserCallFromThread);
	
	lexicalThread.join();
	parserThread.join();
	return 0;
}

