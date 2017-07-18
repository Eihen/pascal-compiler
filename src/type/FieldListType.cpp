#include "FieldListType.h"

FieldListType::FieldListType(list<string> fieldList) : Type(TYPE_FIELD_LIST)
{
    this->fieldList = fieldList;
}

FieldListType::~FieldListType()
{
}

