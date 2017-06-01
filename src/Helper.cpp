#include "Helper.h"

using namespace std;

Helper::Helper()
{
}

Helper::~Helper()
{
}

bool Helper::isSeparator(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

bool Helper::isDelimiter(char c) {
    return isSeparator(c) || isSymbol(string(1, c)) != ERR_CHAR;
}

bool Helper::isNumber(char c) {
    return c >= '0' && c <= '9';
}

bool Helper::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

int Helper::isKeyword(string word) {
    static map<string, int> keywords = {
		//Palavras Chave
		{"AND", KW_AND}, {"ARRAY", KW_ARRAY}, {"ASM", KW_ASM}, {"BEGIN", KW_BEGIN}, {"BREAK", KW_BREAK}, {"CASE", KW_CASE}, {"CONST", KW_CONST}, {"CONSTRUCTOR", KW_CONSTRUCTOR}, {"CONTINUE", KW_CONTINUE}, {"DESTRUCTOR", KW_DESTRUCTOR}, {"DIV", KW_DIV}, {"DO", KW_DO}, {"DOWNTO", KW_DOWNTO}, {"ELSE", KW_ELSE}, 
		{"END", KW_END}, {"FALSE", KW_FALSE}, {"FILE", KW_FILE}, {"FOR", KW_FOR}, {"FUNCTION", KW_FUNCTION}, {"GOTO", KW_GOTO}, {"IF", KW_IF}, {"IMPLEMENTATION", KW_IMPLEMENTATION}, {"IN", KW_IN}, {"INLINE", KW_INLINE}, {"INTERFACE", KW_INTERFACE}, {"LABEL", KW_LABEL}, {"MOD", KW_MOD}, {"NIL", KW_NIL}, {"NOT", KW_NOT}, 
		{"OBJECT", KW_OBJECT}, {"OF", KW_OF}, {"ON", KW_ON}, {"OPERATOR", KW_OPERATOR}, {"OR", KW_OR}, {"PACKED", KW_PACKED}, {"PROCEDURE", KW_PROCEDURE}, {"PROGRAM", KW_PROGRAM}, {"RECORD", KW_RECORD}, {"REPEAT", KW_REPEAT}, {"SET", KW_SET}, {"SHL", KW_SHL}, {"SHR", KW_SHR}, {"STRING", KW_STRING}, {"THEN", KW_THEN}, 
		{"TO", KW_TO}, {"TRUE", KW_TRUE}, {"TYPE", KW_TYPE}, {"UNIT", KW_UNIT}, {"UNTIL", KW_UNTIL}, {"USES", KW_USES}, {"VAR", KW_VAR}, {"WHILE", KW_WHILE}, {"WITH", KW_WITH}, {"XOR", KW_XOR},
		
		//TIPOS
		{"INTEGER", TYPE_INT}, {"REAL", TYPE_REAL}, {"BOOLEAN", TYPE_BOOLEAN}, {"CHARACTER", TYPE_CHAR}, {"BYTE", TYPE_BYTE}, {"STRING", TYPE_STRING} 
	};
	map<string,int>::iterator it;
	if ((it = keywords.find(toUpper(word))) != keywords.end())
	{
		return it->second;
	}
	else
	{
		return IDENTIFIER;
	}
}

bool Helper::isSymbolPrefix(char c) {
	return c == '(' || c == '*' || c == '.' || c == '/' || c == '<' || c == '>' || c == ':' || c == '+' || c == '-' || c == '/';
}

int Helper::isSymbol(string word) {
    static map<string, int> symbols = {
		{"[", SMB_OPEN_BRACKET}, {"]", SMB_CLOSE_BRACKET}, {"(", SMB_OPEN_PARENT}, {")", SMB_CLOSE_PARENT}, {".", SMB_DOT}, {",", SMB_COMMA}, {":", SMB_COLON}, {"^", SMB_CARET},
		{"@", SMB_AT}, {"{", SMB_OPEN_BRACE}, {"}", SMB_CLOSE_BRACE}, {"$", SMB_DOLLAR}, {"#", SMB_NUM_SIGN}, {"(*", SMB_OPEN_PARENT_ASTERISK}, {"*)", SMB_CLOSE_PARENT_ASTERISK},
		{"(.", SMB_OPEN_PARENT_DOT}, {".)", SMB_CLOSE_PARENT_DOT}, {"//", SMB_SLASH_SLASH}, {";", SMB_SEMICOLON},
		
		{"+", OP_PLUS}, {"-", OP_MINUS}, {"*", OP_MULT}, {"/", OP_DIV}, {"%", OP_MOD}, {"=", OP_EQUALS}, {"<>", OP_DIFF}, 
		{">", OP_HIGHER}, {"<", OP_LOWER}, {">=", OP_HIGHER_EQUALS}, {"<=", OP_LOWER_EQUALS}, {":", OP_COLON}, 
		{"&", OP_BIN_AND}, {"|", OP_BIN_OR}, {"!", OP_BIN_NOT}, {"~", OP_BIN_COMPL}, {"<<", OP_SHIFT_LEFT}, 
		{">>", OP_SHIFT_RIGHT}, {":=", OP_ASSIGN}, {"+=", OP_PLUS_ASSIGN}, {"-=", OP_MINUS_ASSIGN}, {"*=", OP_MULT_ASSIGN}, 
		{"/=", OP_DIV_ASSIGN}
	};
	map<string,int>::iterator it;
	if ((it = symbols.find(word)) != symbols.end())
	{
		return it->second;
	}
	else
	{
		return ERR_CHAR;
	}
}

string Helper::toUpper(string word)
{
	transform(word.begin(), word.end(), word.begin(), ::toupper);
	return word;
}

