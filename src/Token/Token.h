#ifndef BASETOKEN_HPP
#define BASETOKEN_HPP

#include <string>

using namespace std;

class Token
{
private:
    string mValue;
    int mTipo;
protected:
    void setTipo(int tipo);
public:
    Token(string value) {
        mValue = value;
    }
    string getValue();
    int getTipo();
};

#endif // BASETOKEN_HPP
