#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include <string>
#include "field.h"

class Document{
    private:
        double m_val;
        set <field> m_element;
    public:
        Document(){m_val = 0;}
        ~Document(){}
        void AddField       (field x);
        Field SearchField   (std::string x);
        void AddVal         (double x);
        void ClearVal       ();
};

#endif