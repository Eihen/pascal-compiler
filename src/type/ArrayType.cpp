#include "ArrayType.h"

ArrayType::ArrayType(list<DimensionType> dimensions) : Type(TYPE_ARRAY), dimensions(dimensions)
{
}

list<DimensionType> ArrayType::getDimensions()
{
    return dimensions;
}

ArrayType::~ArrayType()
{
}

