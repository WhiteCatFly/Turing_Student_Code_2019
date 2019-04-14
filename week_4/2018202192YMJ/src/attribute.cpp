#include <string>

#include <fstream>
#include <iostream>

#include "string_utility.h"
#include "token.h"
#include "attribute.h"

Attribute::Attribute(const std::string &name,
                     const std::string &value):
    m_name(name), m_value(value) {}

void Attribute::remove_suf(const std::string &suf)
{
    string_remove_suf(m_value, suf);
}

std::ostream & operator <<(std::ostream &os, const Attribute &attribute)
{
    os << "name: " << attribute.m_name <<
          ", value: " << attribute.m_value;
    return os;
}