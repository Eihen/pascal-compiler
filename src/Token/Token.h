#ifndef BASETOKEN_HPP
#define BASETOKEN_HPP

#include <string>

enum { 
		NUM_FLOAT, NUM_INT, 																											 //Numero
		OP_DOIS_PONTOS, OP_IGUAL, OP_PORCENT, OP_MAIS, OP_MENOS, OP_BARRA, OP_AST, OP_MENOR, OP_MAIOR, OP_E, OP_BARRA_VERT, 			 //Operador
		OP_EXCL, OP_TIL, OP_DESL_ESQ, OP_DESL_DIR, OP_MAIOR_IGUAL, OP_MENOR_IGUAL, OP_DIF, OP_ATRIB,									 //-------------
		PCH_AND, PCH_ARRAY, PCH_ASM, PCH_BEGIN, PCH_BREAK, PCH_CASE, PCH_CONST, PCH_CONSTRUCTOR, PCH_CONTINUE, PCH_DESTRUCTOR,			 //Palavra chave
		PCH_DIV, PCH_DO, PCH_DOWNTO, PCH_ELSE, PCH_END, PCH_FALSE, PCH_FILE, PCH_FOR, PCH_FUNCTION, PCH_GOTO, PCH_IF, PCH_IMPLEMENTATION,//-------------
		PCH_IN, PCH_INLINE, PCH_INTERFACE, PCH_LABEL, PCH_MOD, PCH_NIL, PCH_NOT, PCH_OBJECT, PCH_OF, PCH_ON, PCH_OPERATOR, PCH_OR, 		 //-------------
		PCH_PACKED, PCH_PROCEDURE, PCH_PROGRAM, PCH_RECORD, PCH_REPEAT, PCH_SET, PCH_SHL, PCH_SHR, PCH_STRING, PCH_THEN, 				 //-------------
		PCH_TO, PCH_TRUE, PCH_TYPE, PCH_UNIT, PCH_UNTIL, PCH_USES, PCH_VAR, PCH_WHILE, PCH_WITH, PCH_XOR,								 //-------------
		SMB_ABRE_PARENT, SMB_FECHA_PARENT, SMB_PONT_VIRG, SMB_VIRG, SMB_ABRE_COLCH, SMB_FECHA_COLCH, SMB_PONTO,							 //Simbolo
		ERRO_CHAR, ERRO_TAM, ERRO_FORMATO, 																								 //Erros
		IDENTIFICADOR																													 //Identificador
	 };

using namespace std;

class Token
{
private:
    string mValue;
    int mTipo;
protected:
    void setTipo(int tipo);
public:
    Token(string value) {
        mValue = value;
    }
    string getValue();
    int getTipo();
};

#endif // BASETOKEN_HPP
