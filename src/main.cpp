#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include "LexicalAnalyzer.h"
#include "Parser.h"
#include "TokenQueue.h"

using namespace std;

TokenQueue tokenQueue;

void lexicalCallFromThread(ifstream* file)
{
	LexicalAnalyzer lexicalAnalyzer(file, &tokenQueue);
}

void parserCallFromThread()
{
	Parser parser(&tokenQueue);
}

bool icompare_pred(unsigned char a, unsigned char b)
{
    return std::tolower(a) == std::tolower(b);
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin(), icompare_pred);
}

int main() {
	string fileName;
	
	cout << "Digite o caminho do arquivo a ser compilado: ";
	cin >> fileName;
    
    if (!ends_with(fileName, ".pas"))
    {
        cout << "O arquivo informado deve possuir extensao .pas";
        return 1;
    }
    
    ifstream file(fileName);
    if (file.is_open())
    {
        thread lexicalThread(lexicalCallFromThread, &file);
        thread parserThread(parserCallFromThread);
	
        lexicalThread.join();
        parserThread.join();
        return 0;
    }	

    cout << "Nao foi possivel abrir o arquivo";
    return 1;
	
}

