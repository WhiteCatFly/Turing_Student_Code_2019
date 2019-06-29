#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <string>

class Field{
    friend bool operator < (field x, field y);
    private:
        std::string m_name;
    public:
        field(){}
        field(std::string x) m_name(x); {}
        ~field(){}
        std::string AccessName();
};

#endif
