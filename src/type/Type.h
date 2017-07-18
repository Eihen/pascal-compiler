#ifndef TYPE_H
#define TYPE_H

class Type
{
public:
    Type();
    Type(int code);
    int getCode();
    static const int TYPE_ARRAY = 1000;
    static const int TYPE_FIELD_LIST = 1001;
    static const int TYPE_DIMENSION = 1002;
    static const int TYPE_FILE = 1003;
    static const int TYPE_RECORD = 1004;
    static const int TYPE_SET = 1004;

    virtual ~Type();
private:
    int code;
};

#endif // TYPE_H
