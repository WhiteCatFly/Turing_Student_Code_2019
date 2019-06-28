#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include "field.h"

class Document{
    private:
        set <field> m_element;
    public:
        void AddField       (field x);
        field SearchField   (std::string x);
};

#endif