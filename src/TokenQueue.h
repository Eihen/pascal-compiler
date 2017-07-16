#ifndef TOKENQUEUE_H
#define TOKENQUEUE_H

#include "Token.h"
#include <mutex>
#include <queue>
#include <condition_variable>

namespace std
{
	class TokenQueue
	{
		public:
			TokenQueue();
			~TokenQueue();
			
			void finish();
			void enqueue(Token token);
			Token dequeue();
			
		private:
			bool finished;
			std::mutex lock;
			std::condition_variable not_empty;
			std::queue<Token> tokenQueue;
	};
}

#endif // TOKENQUEUE_H
