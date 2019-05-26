#ifndef _DOM_H
#define _DOM_H

#include <iostream>
#include <string>
#include <vector>

#include "Token.h"
#include "tagString.h"

class DOM
{
private:
    struct Node
    {
        Node *parent;
        std::vector<Node*> child;

        int type;
        bool OPEN_TAG;

        std::string tagName;
        std::string content;
        std::vector<std::pair<std::string, std::string> > attribute;
    
        Node(){}
        Node(Token &token);
        bool isCloseTag();
        void setParent(Node *p);
        void addChild(Node *son);

        void show(int level = 0, bool textOnly = false);
    };
    Node *root, *HEAD;
    
    void deleteTree_(Node *x);
    void showTree_(Node *x, int lv = -1);
    void extractTagName_(Node *node, std::string tagName);
    void extractTagAttr_(std::vector<std::string> &res, Node *node, std::string tagName, std::string attrName);
    void showAllText_(Node *node);
    void DOM_(std::vector<Token> &tokens);

public:
    DOM(std::string rawHTML);
    DOM(std::ifstream &is);
    ~DOM();
    void showTree();
    void extractTagName(std::string tagName);
    std::vector<std::string> extractTagAttr(std::string tagName, std::string attrName);
    void showAllText();

};

#endif