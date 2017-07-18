#ifndef FIELDLISTTYPE_H
#define FIELDLISTTYPE_H

#include "Type.h"
#include <list>
#include <string>

using namespace std;

class FieldListType : public Type
{
public:
    FieldListType(list<string> fieldList);
    ~FieldListType();
private:
    list<string> fieldList;

};

#endif // FIELDLISTTYPE_H
