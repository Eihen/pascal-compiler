#include "TableRow.h"

using namespace std;

TableRow::TableRow(Token _token, int _type)
{
    token = _token;
    type = _type;
}

Token TableRow::getToken()
{
    return token;
}

int TableRow::getType()
{
    return type;
}

TableRow::~TableRow()
{
}

