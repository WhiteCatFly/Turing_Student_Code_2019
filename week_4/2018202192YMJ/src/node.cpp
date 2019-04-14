#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

#include "string_utility.h"
#include "token.h"
#include "attribute.h"
#include "node.h"

Node::Node(): m_parent(nullptr) {}

Node::Node(Node *parent): m_parent(parent) {}

Node::Node(Node *parent,
           std::string tag,
           std::vector<Attribute> attributes,
           std::string contents):
    m_parent(parent), m_tag(tag),
    m_attributes(attributes), m_contents(contents) {}

void Node::extract_attributes(const std::string &token_str)
{
    std::stringstream strm(string_remove_extra_space(token_str));
    std::string str;
    strm >> str;
    while (strm >> str)
    {
        string_remove_suf(str, "/");
        int pos;
        if ((pos = str.find("=")) == std::string::npos
            || (!char_is_quotation(str[pos+1])
                && char_is_quotation(*str.rbegin())))
        {
            m_attributes.rbegin() -> append_value(str);
        }
        else
        {
            std::string pref = str.substr(0, pos);
            std::string suf  = str.substr(pos + 1);
            m_attributes.push_back(Attribute(pref, suf));
        }
    }
}

void Node::indent(std::ostream &os, int indentation) const
{
    while (indentation--)
    {
        os << '\t';
    }
}

void Node::extract_specific_contents(std::string &title,
                                     std::vector<std::string> &contents,
                                     std::vector<std::string> &hrefs)
{
    if (m_tag == "title") title = m_contents;
    for (auto attribute: m_attributes)
    {
        if (attribute.name() == "href")
        {
            hrefs.push_back(attribute.value());
        }
    }
    if (string_has_contents(m_contents))
    {
        contents.push_back(string_escape_tab_newline(m_contents));
    }
    for (auto child: m_children)
    {
        child -> extract_specific_contents(title, contents, hrefs);
    }
}

void Node::output(std::ostream &os, int indentation) const
{
    indent(os, indentation);
    os << "tag: " << m_tag << std::endl;
    if (m_attributes.size() > 0)
    {
        indent(os, indentation);
        os << "- attribute(s):\n";
        for (auto attribute: m_attributes)
        {
            indent(os, indentation);
            os << "-- " << attribute << std::endl;
        }
    }
    if (string_has_contents(m_contents))
    {
        indent(os, indentation);
        os << "- contents: "
           << string_escape_tab_newline(m_contents)
           << std::endl;
    }
    if (m_children.size() > 0)
    {
        indent(os, indentation);
        os << "- child(ren):\n";
        for (auto child: m_children)
        {
            child -> output(os, indentation + 1);
        }
    }
}

void Node::recursive_destruct()
{
    for (auto child: m_children)
    {
        child -> recursive_destruct();
        delete child;
    }
}