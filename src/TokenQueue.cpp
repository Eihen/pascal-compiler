#include "TokenQueue.h"

using namespace std;

TokenQueue::TokenQueue()
{
	finished = false;
}

TokenQueue::~TokenQueue()
{
}

void TokenQueue::finish()
{
	//Trava para que os métodos não sejam executados ao mesmo tempo
	std::unique_lock<std::mutex> l(lock);
	
	//Sinaliza que não há mais tokens para serem adicionadas
	finished = true;
	not_empty.notify_one();
}

void TokenQueue::enqueue(Token* token)
{
	//Trava para que os métodos não sejam executados ao mesmo tempo
	std::unique_lock<std::mutex> l(lock);
	
	//Adiciona a token na lista
    tokenQueue.push(token);
	
	//Desativa a trava de lista vazia
	not_empty.notify_one();
}

Token* TokenQueue::dequeue()
{
	//Trava para enqueue e dequeue não serem acessados ao mesmo tempo
	std::unique_lock<std::mutex> l(lock);
	
	//Trava para lista vazia
	not_empty.wait(l, [this](){return !tokenQueue.empty() || finished;});
	
	//Retira token da lista
    Token* token = tokenQueue.front();
	tokenQueue.pop();
	
	return token;
}