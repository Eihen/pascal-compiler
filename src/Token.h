#ifndef BASETOKEN_H
#define BASETOKEN_H

#include <string>

namespace std
{
	enum { 
		//Literais
		LIT_INT, LIT_FLOAT, LIT_STRING,
		
		//Operadores
		OP_PLUS /* + */, OP_MINUS /* - */, OP_MULT /* * */, OP_DIV /* / */, OP_MOD /* % */, OP_EQUALS /* = */, OP_DIFF /* <> */,
		OP_HIGHER /* > */, OP_LOWER /* < */, OP_HIGHER_EQUALS /* >= */, OP_LOWER_EQUALS /* <= */, OP_COLON /* : */,
		OP_BIN_AND /* & */, OP_BIN_OR /* | */, OP_BIN_NOT /* ! */, OP_BIN_COMPL /* ~ */, OP_SHIFT_LEFT /* << */, 
		OP_SHIFT_RIGHT /* >> */, OP_ASSIGN /* := */, OP_PLUS_ASSIGN /* += */, OP_MINUS_ASSIGN /* -= */, OP_MULT_ASSIGN /* *= */,
		OP_DIV_ASSIGN /* /= */, 
		
		//Palavras Chave
		KW_AND, KW_ARRAY, KW_ASM, KW_BEGIN, KW_BREAK, KW_CASE, KW_CONST, KW_CONSTRUCTOR, KW_CONTINUE, KW_DESTRUCTOR,
		KW_DIV, KW_DO, KW_DOWNTO, KW_ELSE, KW_END, KW_FALSE, KW_FILE, KW_FOR, KW_FUNCTION, KW_GOTO, KW_IF, KW_IMPLEMENTATION,
		KW_IN, KW_INLINE, KW_INTERFACE, KW_LABEL, KW_MOD, KW_NIL, KW_NOT, KW_OBJECT, KW_OF, KW_ON, KW_OPERATOR, KW_OR,
		KW_PACKED, KW_PROCEDURE, KW_PROGRAM, KW_RECORD, KW_REPEAT, KW_SET, KW_SHL, KW_SHR, KW_STRING, KW_THEN,
		KW_TO, KW_TRUE, KW_TYPE, KW_UNIT, KW_UNTIL, KW_USES, KW_VAR, KW_WHILE, KW_WITH, KW_XOR,
		
		//Tipos
		TYPE_INT, TYPE_REAL, TYPE_CHAR, TYPE_STRING, TYPE_BYTE, TYPE_BOOLEAN,
		
		//Símbolos
		SMB_OPEN_BRACKET /* [ */, SMB_CLOSE_BRACKET /* ] */, SMB_OPEN_PARENT /* ( */, SMB_CLOSE_PARENT /* ) */, SMB_DOT /* . */, SMB_COMMA /* , */, SMB_COLON /* : */, SMB_CARET /* ^ */,
		SMB_AT /* @ */, SMB_OPEN_BRACE /* { */, SMB_CLOSE_BRACE /* } */, SMB_DOLLAR /* $ */, SMB_NUM_SIGN /* # */, SMB_OPEN_PARENT_ASTERISK /* (* */, SMB_CLOSE_PARENT_ASTERISK /* *) */,
		SMB_OPEN_PARENT_DOT /* (. */, SMB_CLOSE_PARENT_DOT /* .) */, SMB_SLASH_SLASH /* // */, SMB_DOUBLE_DOT /* .. */, SMB_SEMICOLON /* ; */,
		
		//Erros
		ERR_CHAR, ERR_SIZE, ERR_END_FILE, ERR_FORMAT,
		
		//Identificadores
		IDENTIFIER
	 };

	class Token
	{
		private:
			string value;
			int type, line, column;
		protected:
			void setType(int _type);
		public:
			Token(string _value, int _type, int _line, int _column)
			{
				value = _value;
				type = _type;
				line = _line;
				column = _column;
			}
			string getValue();
			int getType();
			int getLine();
			int getColumn();
			bool isIdentifier();
			bool isType();
            bool isNumber();
	};
}

#endif // BASETOKEN_H
