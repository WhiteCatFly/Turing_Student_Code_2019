#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::pair;

class Node{
    friend class DOMTree;
    public:
        enum TYPE{
            TagNode = 1, TextNode = 2
        };
    private:
        TYPE    _type;
        string  _nodeName;
        map <string,string> _nodeAttributes;
        int     _degree;        // Number of Children
        int     _level;
	Node*	_parent = NULL;
        Node*   _leftMostChild = NULL;
        Node*   _rightSibling = NULL;

        bool isLeaf();
        bool isRoot();
    public:
        Node() = default;
	void visit();
        void setAttribute(string& key, string& value);
};
#endif
