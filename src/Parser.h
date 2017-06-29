#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "TokenQueue.h"
#include "TableRow.h"
#include <map>

namespace std
{
	class Parser
	{
	public:
		Parser(TokenQueue* _tokenQueue);
		~Parser();
		
	private:
		Token* token;
		int type;
        map<Token*, TableRow> table;
		TokenQueue* tokenQueue = NULL;

        bool isIdentifier(int desiredType);
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
