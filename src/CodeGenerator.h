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
        int  getMemCount();
        void allocMemory(unsigned long memorySize);
        void freeMemory(unsigned long memorySize);
        void invert();
        void compare(int _operator);
        //Low priority operation
        void lpOperation(int _operator);
        //High priority operation
        void hpOperation(int _operator);
        void loadConstant(string value);
        void loadVariable(int scope, int address);
        void createTempAddress(int scope, int address);
        void loadFromExpr(int scope, int address);
        void negate();
        void assign(int scope, int address);
        void assignToTempAddress(int scope);

        void startIf();
        void endIf();
        void genElse();

    private:
		ofstream mepaFile;
		int memCount = -1;
        int ifCount = -1;


    };
}

#endif // CODEGENERATOR_H
