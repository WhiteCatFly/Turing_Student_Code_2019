#include "HTMLParser.h"

using namespace std;

int main(){
    ifstream file("test");
    HTMLParser H(file);
    H.show();

    /*DOMTree DT;
    Node* Aptr = DT.makeNode(Node::TagNode, "title", "undefined");
    Node* Bptr = DT.makeNode(Node::TextNode, "#text", "DOMTree");
    Node* Cptr = DT.makeNode(Node::TagNode, "meta", "undefined");
    Node* Dptr = DT.makeNode(Node::TextNode,"e","rw");
    Node* Eptr = DT.makeNode(Node::TagNode,"ee","ew");
    Node* Fptr = DT.makeNode(Node::TextNode,"erw","rwer");
    DT.buildTree(Aptr, Bptr, Cptr);
    DT.buildTree(Bptr, Dptr, Eptr);
    DT.buildTree(Cptr, NULL, Fptr);
    int count = 0;
    DT.nodesCount(Aptr,count);
    cout << count << endl;
    DT.printHierarchy(Aptr);*/

    return 0;
}
