#ifndef _TAGSTRING_H
#define _TAGSTRING_H

#include <string>
#include <vector>
#include <iostream>

#define NPOS (-1)

bool checkCharactor(char x);

std::string getName(std::string &content, int pos);
bool isComment(std::string &content, int pos);
bool isTagName(std::string &content, int pos);

const std::string RAW_TEXT_TAG[] = 
{
    "script",
    "style",
    "textarea",
    "title",
};

bool isSpecialTag(std::string tagName);

int findCommentEnd(std::string &content, int pos);

// </a>
// . 
int findSpecialPair(std::string &content, std::string tagName, int pos);
int findTagEnd(std::string &content, int pos);

bool checkEmpty(int pos);

std::pair<std::string, std::string> analyzeAttr(std::string rawAttr);


void replaceSlash(std::string &rawStr);
std::vector<std::pair<std::string, std::string> > analyzeTag(std::string rawTagStr);

std::string cutSpace(std::string rawStr);
#endif