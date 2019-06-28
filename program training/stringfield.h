#ifndef STRINGFIELD_H_INCLUDED
#define STRINGFIELD_H_INCLUDED

#include <string.h>
#include "field.h"

class StringField : public Field{
    private:
        std::string m_val;
    public:
        StringField(){}
        StringField(std::string name, std::string val) Field(name), m_val(val) {}
        ~StringField(){}
        bool contain    (std::string x);
        bool match      (std::string x);
};

#endif