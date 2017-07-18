#include "DimensionType.h"

DimensionType::DimensionType(string low, string high) : Type(TYPE_DIMENSION)
{
    this->low = low;
    this->high = high;
}

string DimensionType::getLow()
{
    return low;
}

string DimensionType::getHigh()
{
    return high;
}

DimensionType::~DimensionType()
{
}

