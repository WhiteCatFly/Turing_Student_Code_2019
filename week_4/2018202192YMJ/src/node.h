#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node
{
private:
    Node *m_parent;
    std::vector<Node *> m_children;
    std::string m_tag;
    std::vector<Attribute> m_attributes;
    std::string m_contents;
    void indent(std::ostream &os, int indentation) const;
public:
    Node();
    Node(Node *parent);
    Node(Node *parent,
         std::string tag,
         std::vector<Attribute> attributes,
         std::string m_contents);
    inline Node *parent() const
    {
        return m_parent;
    }
    inline void add_child(Node *child)
    {
        m_children.push_back(child);
    }
    inline void set_tag(const std::string &tag)
    {
        m_tag = tag;
    }
    inline void add_contents(const std::string &contents)
    {
        m_contents += contents;
    }
    void extract_attributes(const std::string &token);
    void extract_specific_contents(std::string &title,
                                   std::vector<std::string> &contents,
                                   std::vector<std::string> &hrefs);
    void output(std::ostream &os, int indentation) const;
    void recursive_destruct();
};

#endif