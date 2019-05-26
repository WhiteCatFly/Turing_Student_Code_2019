#include "node.h"

using namespace std;

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

void Node::setAttribute(string& key, string& value){
    _nodeAttributes.insert(pair<string,string>(key,value));
}
