#ifndef Parser_H
#define Parser_H

using std::string;
class Parser
{
    private:
        string head_, body_;
        Parser* father_;
        std::vector<Parser*> son_;
    public:
        Parser() = default;
        void get_father(Parser* father);
        void get_son(Parser* son);
        void get_head(string &head);
        void get_body(string &body);
        void out(std::ostream &out_);
        string body(){return body_;}
        string head(){return head_;}
        Parser* parser_title();
        void parser_link(std::ostream &out);
        void parser_body(std::ostream &out);
        void free();
};
Parser* build_from_stream(std::istream &in);
Parser* build_from_string(string &text);

#endif