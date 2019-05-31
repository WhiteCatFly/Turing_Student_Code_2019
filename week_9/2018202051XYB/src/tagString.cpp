#include <string>
#include <vector>
#include <iostream>

#include "tagString.h"

bool checkCharactor(char x)
{
    if(x >= 'a' && x <= 'z')
        return true;
    if(x >= 'A' && x <= 'Z')
        return true;
    if(x >= '0' && x <= '9')
        return true;
    return x == '_' || x == '!'; // for <!DOCTYPE
}

std::string getName(std::string &content, int pos)
{
    pos++;
    if(content[pos] == '/')
        pos++; 
    for(int i = pos; i < content.length(); i++)
        if(!checkCharactor(content[i]))
            return content.substr(pos, i - pos);
    return "";
}

bool isComment(std::string &content, int pos)
{
    return content.substr(pos + 1, 3) == "!--";
}

bool isTagName(std::string &content, int pos)
{
    pos++;
    if(content[pos] == '/')
        pos++;
    while(checkCharactor(content[pos]))
        pos++;
    if(content[pos] == ' ' || content[pos] == '>')
        return true;
    return false;
}

bool isSpecialTag(std::string tagName)
{
    for(auto x: RAW_TEXT_TAG)
        if(tagName == x)
            return true;
    return false;
}

int findCommentEnd(std::string &content, int pos)
{
    for(int i = pos; i < content.length() - 2; i++)
        if(content.substr(i, 3) == "-->")
            return i + 2;
    return NPOS;
}

int findSpecialPair(std::string &content, std::string tagName, int pos)
{
    tagName = "</" + tagName;
    int nameLen = tagName.length();
    for(int i = pos; i < content.length() - nameLen; i++)
        if(content.substr(i, nameLen) == tagName 
            && (content[i + nameLen] == ' ' || content[i + nameLen] == '>'))
            return i;
    return NPOS;
}

int findTagEnd(std::string &content, int pos)
{
    if(pos == NPOS)
        return pos;
    bool inAttr = false;
    for(int i = pos; i < content.length(); i++)
    {
        if(inAttr == false && content[i] == '>')
            return i;

        if(content[i] == '\"')
            inAttr ^= 1;
    }
    return NPOS;
}

bool checkEmpty(int pos)
{
    return pos == NPOS;
}

std::pair<std::string, std::string> analyzeAttr(std::string rawAttr)
{
    int spaceNum = 0, pos = -1;
    for(int i = 0; i < rawAttr.length(); i++)
        if(rawAttr[i] == '=')
        {
            spaceNum++;
            pos = pos == -1 ? i : pos;
        }
    if(spaceNum == 0)
        return std::pair<std::string, std::string> (rawAttr , "");
    if(spaceNum == 1 || rawAttr[0] != '=')
        return std::pair<std::string, std::string> 
                        (rawAttr.substr(0, pos) , 
                         rawAttr.substr(pos + 1, rawAttr.length() - pos - 1));
    
    spaceNum = 0;
    for(int i = 0; i < rawAttr.length(); i++)
        if(rawAttr[i] == '=')
        {
            spaceNum++;
            if(spaceNum == 2)
            {
                 return std::pair<std::string, std::string> 
                        (rawAttr.substr(0, i) , 
                         rawAttr.substr(i , rawAttr.length() - i));
            }
        }
}

std::vector<std::pair<std::string, std::string> > analyzeTag(std::string rawTagStr)
{
    std::vector<std::pair<std::string, std::string> > ret;
    std::string tagName = getName(rawTagStr, 0);
    if(rawTagStr[1] == '/')
        rawTagStr = rawTagStr.substr(2);
    else 
        rawTagStr = rawTagStr.substr(1);
    
    if(rawTagStr[rawTagStr.length() - 2] == '/' &&
       isspace(rawTagStr[rawTagStr.length() - 3]))
        rawTagStr[rawTagStr.length() - 2] = ' ';

    int lastSpacePos = tagName.length();
    bool inAttr = false;
    for(int i = lastSpacePos + 1; i < rawTagStr.length(); i++)
        if(inAttr == false && rawTagStr[i] == ' ')
        {
            if(i == lastSpacePos + 1)
            {
                lastSpacePos = i;
                continue;
            }
            ret.push_back(analyzeAttr(rawTagStr.substr(lastSpacePos + 1, i - lastSpacePos - 1)));
            lastSpacePos = i;
        }
        else if(rawTagStr[i] == '"')
            inAttr ^= 1;
    if(lastSpacePos + 1 < rawTagStr.length() - 1)
        ret.push_back(analyzeAttr(rawTagStr.substr(lastSpacePos + 1, rawTagStr.length() - lastSpacePos - 2)));
    
    for(auto &x : ret)
    {
        if(x.second[0] == x.second[x.second.length() - 1] &&
           x.second[0] == '"')
            x.second = x.second.substr(1, x.second.length() - 2);
    }
    return ret;
}

std::string cutSpace(std::string rawStr)
{
    int begin = 0, end = rawStr.length() - 1;
    while(begin <= end && isspace(rawStr[begin]))
        begin++;
    while(begin <= end && isspace(rawStr[end]))
        end--;
    if(begin > end)
        return "";
    else 
        return rawStr.substr(begin, end - begin + 1);
}