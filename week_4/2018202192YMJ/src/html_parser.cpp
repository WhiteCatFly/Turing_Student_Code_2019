#include <cstdio>
#include <climits>
#include <cstdlib>

#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "string_utility.h"
#include "token.h"
#include "attribute.h"
#include "node.h"
#include "html_parser.h"

const std::string HTML_Parser::EMPTY_ELEMENT_TAGS[] =
{
    "area",
    "base",
    "br",
    "col",
    "colgroup",
    "command",
    "embed",
    "hr",
    "img",
    "input",
    "keygen",
    "link",
    "meta",
    "param",
    "source",
    "track",
    "wbr"
};

HTML_Parser::HTML_Parser(const std::string &str, Mode mode)
{
    switch(mode)
    {
    case URL:
        if (system(("wget -o wget-log -O web.txt " + str).c_str()))
        {
            std::cerr << "error: wget failed\n";
            exit(1);
        }
        {
            std::fstream fin("web.txt");
            if (fin.is_open())
            {
                int c;
                while ((c = fin.get()) != EOF)
                {
                    m_html_contents += (char) c;
                }
            }
            else
            {
                std::cerr << "error: cannot open file \"web.txt\"\n";
                exit(1);
            }
        }
        break;
    case FILE:
        {
            std::fstream fin(str);
            if (fin.is_open())
            {
                int c;
                while ((c = fin.get()) != EOF)
                {
                    m_html_contents += (char) (unsigned char) c;
                }
            }
            else
            {
                std::cerr << "error: cannot open file \"" + str + "\"\n";
                exit(1);
            }
        }
        break;
    case STRING:
        m_html_contents = str;
        break;
    default:
        std::cerr << "error: unknown argument for HTML_Parser constructor: " << mode << std::endl;
        exit(1);
        break;
    }
}

std::vector<Token> HTML_Parser::extract_tokens() const
{
    std::vector<Token> extracted_tokens;
    auto search_pos = m_html_contents.cbegin();
    std::smatch match;
    std::regex regex_token("<((!--[\\s\\S]*?--)|([^>]*))>");
    while (std::regex_search(search_pos, m_html_contents.cend(), match, regex_token))
    {
        search_pos = match.suffix().first;
        std::ssub_match unmatched = match.prefix();
        if (unmatched.length() > 0)
        {
            extracted_tokens.push_back(Token(unmatched.str(), Token::TEXT));
        }
        std::ssub_match matched = match[1];
        extracted_tokens.push_back(Token(matched.str(), Token::TAG));
    }
    if (search_pos != m_html_contents.cend())
    {
        extracted_tokens.push_back(
            Token(std::string(search_pos, m_html_contents.cend()), Token::TEXT));
    }
    return extracted_tokens;
}

void HTML_Parser::html_parse()
{
    std::vector<Token> extracted_tokens = extract_tokens();
    Node* current = nullptr;
    for (auto token: extracted_tokens)
    {
        if (token.is_tag())
        {
            if (string_begin_with(std::string(token), "!"))
            {
                continue;
            }
            if (string_begin_with(std::string(token), "/"))
            {
                current = current -> parent();
            }
            else
            {
                Node *new_node = new Node(current);
                if (current != nullptr)
                {
                    current -> add_child(new_node);
                }
                else
                {
                    m_root_nodes.push_back(new_node);
                }
                new_node -> set_tag(string_first_part(std::string(token)));
                new_node -> extract_attributes(std::string(token));
                if (std::find(std::begin(EMPTY_ELEMENT_TAGS),
                              std::end(EMPTY_ELEMENT_TAGS),
                              string_first_part(std::string(token)))
                    == std::end(EMPTY_ELEMENT_TAGS))
                {
                    current = new_node;
                }
            }
        }
        else
        {
            if (string_has_contents(std::string(token)))
            {
                if (current != nullptr)
                {
                    current -> add_contents(std::string(token));
                }
            }
        }
    }
}

void HTML_Parser::extract_specific_contents()
{
    for (auto node: m_root_nodes)
    {
        node -> extract_specific_contents(m_title, m_contents, m_hrefs);
    }
}

void HTML_Parser::output_specific_contents() const
{
    std::ofstream fout;
    fout.open("title.txt");
    if (fout.is_open())
    {
        fout << m_title << std::endl;
        std::clog << "title of the html has been written to \"title.txt\"" << std::endl;
    }
    else
    {
        std::cerr << "error: cannot open file \"title.txt\"" << std::endl;
    }
    fout.close();
    fout.open("contents.txt");
    if (fout.is_open())
    {
        for (auto contents: m_contents)
        {
            fout << contents << std::endl;
        }
        std::clog << "contents of the html has been written to \"contents.txt\"" << std::endl;
    }
    else
    {
        std::cerr << "error: cannot open file \"contents.txt\"" << std::endl;
    }
    fout.close();
    fout.open("hrefs.txt");
    if (fout.is_open())
    {
        for (auto href: m_hrefs)
        {
            fout << href << std::endl;
        }
        std::clog << "hrefs of the html has been written to \"hrefs.txt\"" << std::endl;
    }
    else
    {
        std::cerr << "error: cannot open file \"hrefs.txt\"" << std::endl;
    }
}

std::ostream & operator <<
    (std::ostream &os, const HTML_Parser &html_parser)
{
    for (auto node: html_parser.m_root_nodes)
    {
        node -> output(os, 0);
    }
    return os;
}

HTML_Parser::~HTML_Parser()
{
    for (auto node: m_root_nodes)
    {
        node -> recursive_destruct();
        delete node;
    }
}