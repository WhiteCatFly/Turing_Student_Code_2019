#include "DOMTree.h"

using namespace std;

DOMTree::DOMTree(string& treeLanguage){  // File must have special format
    initializeTree(treeLanguage);
}

Node* DOMTree::makeNode(Node::TYPE t, string newname, string newvalue){
    Node* ptr;
    ptr = new Node;
    if (!ptr)  {return NULL;}
    ptr -> _type = t;
    ptr -> _nodeName = newname;
    ptr -> _nodeValue = newvalue;
    ptr -> _leftMostChild = NULL;
    ptr -> _rightSibling = NULL;
    return ptr;
}

void DOMTree::buildTree(Node* root, Node* leftMostChild, Node* rightSibling){
    root -> _leftMostChild = leftMostChild;
    root -> _rightSibling  = rightSibling;
    leftMostChild -> _parent = root;
    rightSibling  -> _parent = root -> _parent;
}

void DOMTree::initializeTree(string& treeLanguage){
    stringstream ss;
    ss << treeLanguage;
    string temp;
    while (getline(ss,temp)){
        cout << "f**k" << endl;
    }
}

void DOMTree::nodesCount(Node* root, int& count){
    if (root != NULL)
    {
        count++;
        nodesCount(root -> _leftMostChild, count);
        nodesCount(root -> _rightSibling, count);
    }
}

void DOMTree::printHierarchy(Node* root){
    queue <Node*> WaitingToPrint;
    Node* p = root;

    WaitingToPrint.push(root);
    while( !WaitingToPrint.empty() ){
        p = WaitingToPrint.front();
        cout << p -> _type << endl;
        WaitingToPrint.pop();
        if (p -> _leftMostChild != NULL){
            WaitingToPrint.push(p -> _leftMostChild);
        }
        if (p -> _rightSibling != NULL){
            WaitingToPrint.push(p -> _rightSibling);
        }
    }
}

