#ifndef DIMENSIONTYPE_H
#define DIMENSIONTYPE_H

#include "Type.h"
#include <string>

using namespace std;

class DimensionType : public Type
{
public:
    DimensionType(string low, string high);
    string getLow();
    string getHigh();
    ~DimensionType();
private:
    string low;
    string high;

};

#endif // DIMENSIONTYPE_H
