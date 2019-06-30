#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include <set>
#include <string>
#include "field.h"

class Document{
    private:
        double m_val;
        std::set <Field> m_element;
    public:
        Document(){m_val = 0;}
        ~Document(){}
        void AddField       (Field x);
        Field SearchField   (std::string x);
        void AddVal         (double x);
        void ClearVal       ();
};

#endif