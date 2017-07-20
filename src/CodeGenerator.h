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
        void remove();

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

        int startIf();
        void genElse(int ifNumeber);
        void endIf(int ifNumber);

        int startWhile();
        void evaluateWhile(int whileNumber);
        void endWhile(int whileNumber);
        void goTo(string labelNumber);

    private:
		string fileName;
		ofstream mepaFile;
		int memCount = -1;
        int ifCount = -1;
        int whileCount = -1;


    };
}

#endif // CODEGENERATOR_H
