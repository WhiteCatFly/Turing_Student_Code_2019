#include "DOMTree.h"

DOMTree::DOMTree(string& treeLanguage){  // Input must have special format
    initializeTree(treeLanguage);
}

Node::TYPE DOMTree::findNodeType(string& treeSentence){
	string temp = treeSentence.substr(0,1);
	int type = stoi(temp);
	Node::TYPE nodetype = (Node::TYPE)type;
	return nodetype;
}

string DOMTree::findNodeName(string& treeSentence){
	string nodename;
	if (treeSentence[0] == '1'){
		if (treeSentence.find(" ") != treeSentence.npos){
			nodename = treeSentence.substr(1, treeSentence.find(" ") - 1);
		}
		else {
			nodename = treeSentence.substr(1,treeSentence.size() - 1);
		}
	}
	else if (treeSentence[0] == '2'){
		nodename = treeSentence.substr(1,treeSentence.size() - 1);
	}
	return nodename;
}

map <string,string> DOMTree::findNodeAttribute(string& treeSentence){
	map <string,string> attribute;
	Node::TYPE nodetype = findNodeType(treeSentence);
	stringstream ss;
    ss << treeSentence;
	int count = 0;
	string singleAttribute;
	if (nodetype == Node::TagNode){
		while (getline(ss,singleAttribute,' ')){
			if (count == 0){
				count ++;
				continue;
			}
			string key;
			string value;
			key = singleAttribute.substr(0,singleAttribute.find("="));
			size_t startpos = singleAttribute.find("\"") + 1;
			value = singleAttribute.substr(startpos,singleAttribute.size() - startpos - 1);
			attribute.insert(make_pair(key,value));
			count ++;
		}
	}
	return attribute;
}

Node* DOMTree::makeNode(Node::TYPE t, string newname, map <string,string> newattribute){
    Node* newnode = new Node;
    if (!newnode)  {return NULL;}
    newnode -> _type = t;
    newnode -> _nodeName = newname;
	newnode -> _nodeAttributes = newattribute;
    newnode -> _leftMostChild = NULL;
    newnode -> _rightSibling = NULL;
    return newnode;
}

void DOMTree::buildTree(Node* root, Node* leftMostChild, Node* rightSibling){
    root -> _leftMostChild = leftMostChild;
    root -> _rightSibling  = rightSibling;
}

void DOMTree::initializeTree(string& treeLanguage){
    stringstream ss;
    ss << treeLanguage;
    string temp;
	int count = 0;
    while (getline(ss,temp)){
		Node::TYPE nodeType = findNodeType(temp);
		string nodeName = findNodeName(temp);
		map <string,string> nodeAttribute = findNodeAttribute(temp);

		if ((nodeName[0] == '/') && (nodeType == Node::TagNode)){
			nodeName.erase(0,1);
			stack <Node*> WaitingList;

			while( _nodeList.top() -> _nodeName != nodeName ){
				WaitingList.push(_nodeList.top());
				_nodeList.pop();
			}

			Node* ptr = NULL;
			for (int i = 0; i < WaitingList.size(); i++){
				if (i == 0){
					ptr = WaitingList.top();
					_nodeList.top() -> _leftMostChild = ptr;
					continue;
				}
				else{
					ptr -> _rightSibling = WaitingList.top();
				}
				ptr = ptr -> _rightSibling;
			}
		}
		else if ( (nodeName[0] == '!') || (nodeName[0] == '-' ) ){
			continue;
		}
		else{
			Node* newnode = makeNode(nodeType,nodeName,nodeAttribute);
			_nodeList.push(newnode);
		}
		count ++;
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
        p -> visit();    // Output
        WaitingToPrint.pop();
        if (p -> _leftMostChild != NULL){
            WaitingToPrint.push(p -> _leftMostChild);
        }
        while (p -> _rightSibling != NULL){
            p = p -> _rightSibling;
            p -> visit();
            if (p -> _leftMostChild != NULL){
                WaitingToPrint.push(p -> _leftMostChild);
            }
        }
    }
}


