#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "TokenQueue.h"

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
		TokenQueue* tokenQueue = NULL;

		void getToken();
		void constant();
		void sitype();
		//Auxiliar para filist
		void aux_filist_p1();
		void aux_filist_p2();
		void aux_filist_p3();
		void filist();
		void infipo();
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
