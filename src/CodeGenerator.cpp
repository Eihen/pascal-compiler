#include "CodeGenerator.h"

using namespace std;

CodeGenerator::CodeGenerator()
{
}

CodeGenerator::~CodeGenerator()
{

}

void CodeGenerator::begin(string fileName)
{
    mepaFile.open(fileName + ".mepa");
    mepaFile << "INPP\n";
}

void CodeGenerator::end()
{
    mepaFile << "PARA";
}

void CodeGenerator::label(string labelNum)
{
    mepaFile << "LABEL" << labelNum << ":\n";
}

int CodeGenerator::variables(unsigned long count)
{
    mepaFile << "AMEM " << count << "\n";
    varCount += count;
    return varCount;
}

void CodeGenerator::invert()
{
    mepaFile << "INVR\n";
}

void CodeGenerator::compare(int _operator)
{
    switch(_operator)
    {
        case OP_EQUALS:
            mepaFile << "CMIG\n";
            break;
        case OP_LOWER:
            mepaFile << "CMME\n";
            break;
        case OP_HIGHER:
            mepaFile << "CMMA\n";
            break;
        case OP_DIFF:
            mepaFile << "CMDG\n";
            break;
        case OP_LOWER_EQUALS:
            mepaFile << "CMEG\n";
            break;
        case OP_HIGHER_EQUALS:
            mepaFile << "CMAG\n";
            break;
        default: break;
    }
}

void CodeGenerator::lpOperation(int _operator)
{
    switch(_operator)
    {
        case OP_PLUS:
            mepaFile << "SOMA\n";
            break;
        case OP_MINUS:
            mepaFile << "SUBT\n";
            break;
        case KW_OR:
            mepaFile << "DISJ\n";
            break;
        default: break;
    }
}

void CodeGenerator::hpOperation(int _operator)
{
    switch(_operator)
    {
        case OP_MULT:
            mepaFile << "MULT\n";
            break;
        case OP_DIV:
            mepaFile << "DIVI\n";
            break;
        case KW_AND:
            mepaFile << "CONJ\n";
            break;
        default: break;
    }
}

void CodeGenerator::loadConstant(string value)
{
    mepaFile << "CRCT " << value << "\n";
}
