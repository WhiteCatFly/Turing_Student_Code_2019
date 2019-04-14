#ifndef TREE_H
#define TREE_H

using std::string;
class Tree
{
    private:
        string head_, body_;
        Tree* father_;
        std::vector<Tree*> son_;
    public:
        Tree() = default;
        void get_father(Tree* father);
        void get_son(Tree* son);
        void get_head(string &head);
        void get_body(string &body);
        void out(std::ostream &out_);
        string body()
        {
            return body_;
        }
        string head()
        {
            return head_;
        }
        Tree* parser_title();
        void parser_link(std::ostream &out);
        void parser_body(std::ostream &out);
};
Tree* build_from_stream(std::istream &in);
Tree* build_from_string(string &text);

#endif