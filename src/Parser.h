#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "TokenQueue.h"
#include "entry/VarEntry.h"
#include "entry/ConstEntry.h"
#include "entry/TypeEntry.h"
#include "entry/FieldEntry.h"
#include "entry/FunctionEntry.h"
#include "entry/ProcedureEntry.h"
#include "entry/SymbolTableEntry.h"
#include <map>
#include <iostream>

namespace std
{
	class Parser
	{
	public:
		Parser(TokenQueue* _tokenQueue);
		~Parser();
		
	private:
		Token token;
		int type;
        map<string, VarEntry> varTable;
        map<string, ConstEntry> constTable;
        map<string, TypeEntry> typeTable;
        map<string, FieldEntry> fieldTable;
        map<string, FunctionEntry> functionTable;
        map<string, ProcedureEntry> procedureTable;
		TokenQueue* tokenQueue = NULL;
		std::queue<string> errorQueue;

        template<class T> bool isIdentifier(map<string, T> table);
        string tokenHash();
        bool verify_and_get(bool condition);
		void getToken();
		void constant();
		void sitype();
		//Auxiliar para filist
		void aux_filist_p1();
		void aux_filist_p2();
		void aux_filist_p3();
		void filist();
		void infipo();
		void factor();
		void term();
		void siexpr();
		void expr();
		void palist();
		void statm();
		void read_type();
		void block();
		void progrm();
		void trataErro(string message);
	};
}

#endif // LEXICALANALISER_H
