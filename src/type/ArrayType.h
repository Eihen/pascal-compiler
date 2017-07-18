#ifndef ARRAYTYPE_H
#define ARRAYTYPE_H

#include "Type.h"
#include "DimensionType.h"
#include <list>

using namespace std;

class ArrayType : public Type
{
public:
    ArrayType(list<DimensionType> dimensions);
    list<DimensionType> getDimensions();
    ~ArrayType();
private:
    list<DimensionType> dimensions;
};

#endif // ARRAYTYPE_H
