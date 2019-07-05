#include "node.h"

bool Node::isLeaf(){
    if (_leftMostChild == NULL){
        return true;
    }
    return false;
}

bool Node::isRoot(){
    if (_parent == NULL){
        return true;
    }
    return false;
}

void Node::visit(){
    cout << _nodeName << endl;
}

void Node::setAttribute(string& key, string& value){
    _nodeAttributes.insert(pair<string,string>(key,value));
}
