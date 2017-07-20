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

int CodeGenerator::getMemCount()
{
    return memCount + 1;
}

void CodeGenerator::allocMemory(unsigned long memorySize)
{
    if (memorySize > 0)
    {
        mepaFile << "AMEM " << memorySize << "\n";
        memCount += memorySize;
    }
}

void CodeGenerator::freeMemory(unsigned long memorySize)
{
    if (memorySize > 0)
    {
        mepaFile << "DMEM " << memorySize << "\n";
        memCount -= memorySize;
    }
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

void CodeGenerator::loadVariable(int scope, int address)
{
    mepaFile << "CRVL " << scope << ", " << address << "\n";
}

void CodeGenerator::createTempAddress(int scope, int address)
{
    memCount++;
    mepaFile << "CRCT " << address << "\n" //Carrega o endereço inicial da variável
             << "SOMA\n" // Soma com o resultado da expressão do infipo
             << "AMEM 1\n" //Aloca memória para armazenar o endereço temporário
             << "ARMZ " << scope << ", " << memCount << "\n"; //Armazena em um espaço de memória
}

void CodeGenerator::loadFromExpr(int scope, int address)
{
    createTempAddress(scope, address);
    //Carrega o valor da váriavel do endereço contido na posição especificada
    mepaFile << "CRVI " << scope << ", " << memCount << "\n"
             << "DMEM 1\n"; //Desaloca a memória do endereço temporário
    memCount--;
}

void CodeGenerator::negate()
{
    mepaFile << "NEGA\n";
}

void CodeGenerator::assign(int scope, int address)
{
    mepaFile << "ARMZ " << scope << ", " << address << "\n";
}

void CodeGenerator::assignToTempAddress(int scope)
{
    //Assume que o endereço temporário foi criado e está na última posição de memória alocada
    //Armazena o valor no topo da pilha na variável do endereço contido na posição especificada
    mepaFile << "ARMI " << scope << ", " << memCount << "\n"
             << "DMEM 1\n"; //Desaloca a memória do endereço temporário
    memCount--;
}

void CodeGenerator::startIf()
{
    ifCount++;
    mepaFile << "DSVF IF" << ifCount << "\n";
}

void CodeGenerator::genElse()
{
    mepaFile << "DSVS IF" << (ifCount + 1) << "\n"
             << "IF" << ifCount << ":\n";
    ifCount++;
}

void CodeGenerator::endIf()
{
    mepaFile << "IF" << ifCount << ":\n";
}


