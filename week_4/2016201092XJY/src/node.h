#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


class Node{
    friend class DOMTree;
    public:
        enum TYPE{
            TagNode = 1, TextNode = 2
        };
    private:
        TYPE    _type;
        string  _nodeName;
        string  _nodeValue;
        map <string,string> _nodeAttributes;
        int     _degree;        // Number of Children
        int     _level;
        Node*   _parent;
        Node*   _leftMostChild = NULL;
        Node*   _rightSibling = NULL;

        bool isLeaf();
        bool isRoot();
    public:
        Node() = default;
        void setAttribute(string& key, string& value);
};
