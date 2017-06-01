#include "Token.h"

class Parser
{
public:
	Parser();
	~Parser();
	
private:
	int simbolo;

	void getToken();
	void constant();
	void sitype();
	void filist();
	void infipo();
	void siexpr();
	void expr();
	void palist();
	void statm();
	void progrm();
	void trataErro();
};
