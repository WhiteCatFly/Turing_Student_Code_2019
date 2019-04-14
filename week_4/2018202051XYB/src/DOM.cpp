#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "DOM.h"
#include "Token.h"
#include "Lexer.h"
#include "tagString.h"

// no close tag
static std::string NO_CLOSE_TAG[] = {
    "area",
    "base",
    "br",
    "col",
    "colgroup",
    "command",
    "embed",
    "hr",
    "img",
    "input",
    "keygen",
    "link",
    "meta",
    "param",
    "source",
    "track",
    "wbr"
};


DOM::Node::Node(Token &token)
{
    if(token.type() == TYPE_TAG)
    {    
        std::string tagContent = token.getStr();
        tagName = getName(tagContent, 0);
        attribute = analyzeTag(tagContent);
        OPEN_TAG = tagContent[1] != '/';
        type = TYPE_TAG;
    }
    if(token.type() == TYPE_TEXT)
    {    
        content = cutSpace(token.getStr());
        type = TYPE_TEXT;
    }
    if(token.type() == TYPE_COMMENT)
    {
        content = token.getStr();
        type = TYPE_COMMENT;
    }
}
bool DOM::Node::isCloseTag()
{
    return !OPEN_TAG;
}
void DOM::Node::setParent(Node *p)
{
    parent = p;
}
void DOM::Node::addChild(Node *son)
{
    child.push_back(son);
}

void DOM::Node::show(int level, bool textOnly)
{
    for(int i = 1; i <= level; i++)
        std::cout << "    ";
    if(type == TYPE_TAG)
    {
        if(!textOnly)
            std::cout << "[TAG] ";
        std::cout << '<' << tagName << '>' <<  "\n";
        for(auto x : attribute)
        {
            for(int i = 1; i <= level; i++)
                std::cout << "    ";
            std::cout << x.first << ":" << x.second << "\n";
        }
    }
    if(type == TYPE_TEXT)
    {
        if(!textOnly)
            std::cout << "[TEXT] ";
        std::cout << content << std::endl;
    }
    if(type == TYPE_COMMENT)
    {
        if(!textOnly)
        {
            std::cout << "[COMMENT] ";
            std::cout << content << std::endl;
        }
    }

}

void DOM::deleteTree_(Node *x)
{
    for(auto son : x->child)
        deleteTree_(son);
    delete x;
}

void DOM::showTree_(Node *x, int lv)
{
    if(x != root && lv != -1) 
        x->show(lv);
    for(auto son : x->child)
        showTree_(son, lv + 1);
}

void DOM::DOM_(std::vector<Token> &tokens)
{
    root = new Node;
    HEAD = root;
    for(auto token : tokens)
    {
        if(token.empty())
            continue;
        Node *newNode = new Node(token);
        if(token.type() == TYPE_TAG)
        {
            if(newNode->isCloseTag())
            {
                Node *cur = HEAD;
                while(cur != root && cur->tagName != newNode->tagName)
                    cur = cur->parent;
                if(cur != root)
                    HEAD = cur->parent;
                delete newNode;
            }
            else
            {
                HEAD->addChild(newNode);
                newNode->setParent(HEAD);
                HEAD = newNode;
            }   
        }
        else 
        {
            HEAD->addChild(newNode);
            newNode->setParent(HEAD);
        }
    }
}

DOM::DOM(std::string rawHTML)
{
    std::vector<Token> tokens = getTokens(rawHTML);
    DOM_(tokens);
}

DOM::DOM(std::ifstream &is)
{
    std::stringstream buffer;
    buffer << is.rdbuf();
    std::string rawHTML = buffer.str();
    std::vector<Token> tokens = getTokens(rawHTML);
    DOM_(tokens);
}

DOM::~DOM()
{
    deleteTree_(root);
    root = nullptr;
    HEAD = nullptr;
}
void DOM::showTree()
{
    showTree_(root);
}

void DOM::extractTagName_(Node *node, std::string tagName)
{
    if(node->tagName == tagName)
    {
        showTree_(node, 0);
        return;
    }
    for(auto x : node->child)
        extractTagName_(x, tagName);
}
void DOM::extractTagName(std::string tagName)
{
    extractTagName_(root, tagName);
}

void DOM::extractTagAttr_(Node *node, std::string tagName, std::string attrName)
{
    if(node->tagName == tagName)
    {
        for(auto x : node->attribute)
            if(x.first == attrName)
                std::cout << x.first << "=\""
                            << x.second << "\"\n";
    }
    for(auto x : node->child)
        extractTagAttr_(x, tagName, attrName);
}

void DOM::extractTagAttr(std::string tagName, std::string attrName)
{
    extractTagAttr_(root, tagName, attrName);
}

void DOM::showAllText_(Node *node)
{
    if(node->type == TYPE_TEXT)
        node->show(0, true);
    else if(isSpecialTag(node->tagName))
        return;
    for(auto x : node->child)
        showAllText_(x);
}
void DOM::showAllText()
{
    showAllText_(root);
}

