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
#include "type/ArrayType.h"
#include "type/DimensionType.h"
#include "type/FieldListType.h"
#include "type/OfType.h"
#include "type/Type.h"
#include "CodeGenerator.h"
#include <map>
#include <iostream>
#include <list>

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
        int previousScope = 0;
		int currentScope = 0;
        map<string, VarEntry&> varTable;
        map<string, ConstEntry&> constTable;
        map<string, TypeEntry&> typeTable;
        map<string, FieldEntry&> fieldTable;
        map<string, FunctionEntry&> functionTable;
        map<string, ProcedureEntry&> procedureTable;
		TokenQueue* tokenQueue = NULL;
		std::queue<string> errorQueue;
        CodeGenerator codeGenerator;

        template<class T> bool isIdentifier(map<string, T&> table, int scope);
        template<class T> bool isIdentifier(map<string, T&> table);
		template<class T> bool insertSymbol(map<string, T&>* table, T& item, string errorMessage, int scope);
        template<class T> bool insertSymbol(map<string, T&>* table, T& item, string errorMessage);
        Type& currentTokenType();
        string tokenHash(int scope);
        string tokenHash();
        bool verify_and_get(bool condition);
		void getToken();
		string constant();
		Type& sitype();
		//Auxiliar para filist
		void aux_filist_p1();
		void aux_filist_p2();
		void aux_filist_p3();
		void filist();
		bool infipo();
		void factor();
		void term();
		void siexpr();
		void expr();
		list<SymbolTableEntry> palist();
		void statm();
		Type& read_type();
		void block();
		void progrm();
		void trataErro(string message);
	};
}

#endif // LEXICALANALISER_H
