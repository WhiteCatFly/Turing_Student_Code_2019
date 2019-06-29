#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include <string>
#include "field.h"

class Document{
    private:
        set <field> m_element;
    public:
        void AddField       (field x);
        Field SearchField   (std::string x);
};

#endif