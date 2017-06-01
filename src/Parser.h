#include "Token.h"

class Parser
{
public:
	Parser();
	~Parser();
	
private:
    Token* token;
	int type;

	void getToken();
	void constant();
	void sitype();
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
