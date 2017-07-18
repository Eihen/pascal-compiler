#ifndef OFTYPE_H
#define OFTYPE_H

#include "Type.h"

class OfType : public Type
{
public:
    OfType(int code, Type ofType);
    Type getOfType();
    ~OfType();
private:
    Type ofType;
};

#endif // OFTYPE_H
