#include <string>
#include <iostream>

#include "token.h"
#include "string_utility.h"

Token::Token(const std::string &contents, Type type):
    m_contents(contents), m_type(type) {}

std::ostream & operator <<(std::ostream &os, const Token &token)
{
    os << (token.m_type == Token::Type::TAG ? "TAG: " : "TEXT: ")
       << token.m_contents;
    return os;
}