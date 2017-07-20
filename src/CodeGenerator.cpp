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
    this->fileName = fileName + ".mepa";
    mepaFile.open(fileName + ".mepa");
    mepaFile << "\tINPP\n";
}

void CodeGenerator::end()
{
    mepaFile << "\tPARA";
    mepaFile.close();
}

void CodeGenerator::remove()
{
    std::remove(fileName.c_str());
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
        mepaFile << "\tAMEM " << memorySize << "\n";
        memCount += memorySize;
    }
}

void CodeGenerator::freeMemory(unsigned long memorySize)
{
    if (memorySize > 0)
    {
        mepaFile << "\tDMEM " << memorySize << "\n";
        memCount -= memorySize;
    }
}

void CodeGenerator::invert()
{
    mepaFile << "\tINVR\n";
}

void CodeGenerator::compare(int _operator)
{
    switch(_operator)
    {
        case OP_EQUALS:
            mepaFile << "\tCMIG\n";
            break;
        case OP_LOWER:
            mepaFile << "\tCMME\n";
            break;
        case OP_HIGHER:
            mepaFile << "\tCMMA\n";
            break;
        case OP_DIFF:
            mepaFile << "\tCMDG\n";
            break;
        case OP_LOWER_EQUALS:
            mepaFile << "\tCMEG\n";
            break;
        case OP_HIGHER_EQUALS:
            mepaFile << "\tCMAG\n";
            break;
        default: break;
    }
}

void CodeGenerator::lpOperation(int _operator)
{
    switch(_operator)
    {
        case OP_PLUS:
            mepaFile << "\tSOMA\n";
            break;
        case OP_MINUS:
            mepaFile << "\tSUBT\n";
            break;
        case KW_OR:
            mepaFile << "\tDISJ\n";
            break;
        default: break;
    }
}

void CodeGenerator::hpOperation(int _operator)
{
    switch(_operator)
    {
        case OP_MULT:
            mepaFile << "\tMULT\n";
            break;
        case OP_DIV:
            mepaFile << "\tDIVI\n";
            break;
        case KW_AND:
            mepaFile << "\tCONJ\n";
            break;
        default: break;
    }
}

void CodeGenerator::loadConstant(string value)
{
    mepaFile << "\tCRCT " << value << "\n";
}

void CodeGenerator::loadVariable(int scope, int address)
{
    mepaFile << "\tCRVL " << scope << ", " << address << "\n";
}

void CodeGenerator::createTempAddress(int scope, int address)
{
    memCount++;
    mepaFile << "\tCRCT " << address << "\n" //Carrega o endereço inicial da variável
             << "\tSOMA\n" // Soma com o resultado da expressão do infipo
             << "\tAMEM 1\n" //Aloca memória para armazenar o endereço temporário
             << "\tARMZ " << scope << ", " << memCount << "\n"; //Armazena em um espaço de memória
}

void CodeGenerator::loadFromExpr(int scope, int address)
{
    createTempAddress(scope, address);
    //Carrega o valor da váriavel do endereço contido na posição especificada
    mepaFile << "\tCRVI " << scope << ", " << memCount << "\n"
             << "\tDMEM 1\n"; //Desaloca a memória do endereço temporário
    memCount--;
}

void CodeGenerator::negate()
{
    mepaFile << "\tNEGA\n";
}

void CodeGenerator::assign(int scope, int address)
{
    mepaFile << "\tARMZ " << scope << ", " << address << "\n";
}

void CodeGenerator::assignToTempAddress(int scope)
{
    //Assume que o endereço temporário foi criado e está na última posição de memória alocada
    //Armazena o valor no topo da pilha na variável do endereço contido na posição especificada
    mepaFile << "\tARMI " << scope << ", " << memCount << "\n"
             << "\tDMEM 1\n"; //Desaloca a memória do endereço temporário
    memCount--;
}

int CodeGenerator::startIf()
{
    ifCount += 2;
    mepaFile << "\tDSVF IF" << (ifCount - 1) << "\n";
    return ifCount;
}

void CodeGenerator::genElse(int ifNumber)
{
    mepaFile << "\tDSVS IF" << ifNumber << "\n"
             << "IF" << (ifNumber - 1) << ":\n";
    ifCount++;
}

void CodeGenerator::endIf(int ifNumber)
{
    mepaFile << "IF" << ifNumber << ":\n";
}

int CodeGenerator::startWhile()
{
    whileCount+=2;
    mepaFile << "WHILE" << whileCount - 1 << ":\n";
    return whileCount;
}

void CodeGenerator::evaluateWhile(int whileNumber)
{
    mepaFile << "\tDSVF WHILE" << whileNumber << "\n";
}


void CodeGenerator::endWhile(int whileNumber)
{
    mepaFile << "\tDSVS WHILE" << whileNumber - 1 << "\n";
    mepaFile << "WHILE" << whileNumber << ":\n";
}

void CodeGenerator::goTo(string labelNumber)
{
    mepaFile << "\t DSVS LABEL" << labelNumber << "\n";
}
