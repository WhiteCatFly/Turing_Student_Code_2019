#ifndef HTML_PARSER_H_INCLUDED
#define HTML_PARSER_H_INCLUDED
class HtmlParser {
   private:
    std::string url;
    std::string html_content;
    std::vector<TagNode *> tags;
    std::vector<TagNode *> extract_tag(std::string &str);

   public:
    HtmlParser() {}
    HtmlParser(const std::string save_path);
    void print();
    std::string get_url() const { return url; }
    std::vector<std::string> parse_text() const;
    std::vector<std::string> parse_href() const;
    std::string parse_title() const;
    void erase_empty_tags();
};

#endif