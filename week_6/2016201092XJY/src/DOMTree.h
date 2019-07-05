#ifndef __DOMTREE_H__
#define __DOMTREE_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include "node.h"

using std::stack;
using std::stringstream;
using std::queue;

class DOMTree{
    private:
        Node* _root;
        stack <Node*> _nodeList;

        bool  			isEmpty();
	Node::TYPE 		findNodeType(string& treeSentence);
	string 			findNodeName(string& treeSentence);
	map <string,string> 	findNodeAttribute(string& treeSentence);
    public:
        DOMTree() = default;
        DOMTree(string& treeLanguage);

        //void clear();
	Node* getRoot () { return _root; }
        Node* makeNode(Node::TYPE t, string newname, map <string,string> newattribute);
        void buildTree(Node* root, Node* leftMostChild, Node* rightSibling);
        void initializeTree(string& treeLanguage);
        void nodesCount(Node* root, int& count);
        void printHierarchy(Node* root);
        
};
#endif
