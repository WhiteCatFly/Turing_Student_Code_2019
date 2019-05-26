#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "node.h"

using namespace std;

class DOMTree{
    private:
        Node* _root;
        vector <string> _nodeList;

        bool isEmpty();
    public:
        DOMTree() = default;
        DOMTree(string& treeLanguage);
        //void clear();

        Node* makeNode(Node::TYPE t, string newname, string newvalue);
        void buildTree(Node* root, Node* leftMostChild, Node* rightSibling);
        void initializeTree(string& treeLanguage);
        void nodesCount(Node* root, int& count);
        void printHierarchy(Node* root);
        void getNodeList();
};
