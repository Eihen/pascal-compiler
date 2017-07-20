#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Token.h"
#include <fstream>

namespace std
{
	class CodeGenerator
	{
	public:
        CodeGenerator();
		~CodeGenerator();

        void begin(string fileName);
        void end();

        void label(string labelName);
        int variables(unsigned long count);
        void invert();
        void compare(int _operator);
        //Low priority operation
        void lpOperation(int _operator);
        //High priority operation
        void hpOperation(int _operator);
        void loadConstant(string value);
		
	private:
		ofstream mepaFile;
		int varCount = -1;

	};
}

#endif // CODEGENERATOR_H
