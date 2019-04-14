#ifndef HTML_PARSER_H_INCLUDED
#define HTML_PARSER_H_INCLUDED

class HTML_Parser
{
private:
    static const std::string EMPTY_ELEMENT_TAGS[];
    std::string m_html_contents;
    std::vector<Node *> m_root_nodes;
    std::string m_title;
    std::vector<std::string> m_contents;
    std::vector<std::string> m_hrefs;
    std::vector<Token> extract_tokens() const;
public:
    enum Mode
    {
        URL, FILE, STRING
    };
    HTML_Parser() = default;
    HTML_Parser(const std::string &str, Mode mode);
    void html_parse();
    void extract_specific_contents();
    void output_specific_contents() const;
    friend std::ostream & operator <<
        (std::ostream &os, const HTML_Parser &html_parser);
    ~HTML_Parser();
};

#endif