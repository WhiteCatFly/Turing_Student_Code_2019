#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include "field.h"

class Document{
    private:
        set <field> m_element;
    public:
        void addField       (field x);
        field searchField   (std::string x);
};

#endif