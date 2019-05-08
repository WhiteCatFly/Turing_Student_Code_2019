#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"
#include "Token.h"
#include "tagString.h"

std::vector<Token> getTokens(std::string rawString)
{
    std::vector<Token> tokens;
    int strLen = rawString.size(),
        pos = 0,
        lastPos = -1;
    while(pos < strLen)
    {
        if(rawString[pos] == '<')
        {
            if(isComment(rawString, pos))
            {
                int endPos = findCommentEnd(rawString, pos);
                if(checkEmpty(endPos))
                    break;
                Token preText(rawString.substr(lastPos + 1, pos - lastPos - 1), TYPE_TEXT),
                      commentTag(rawString.substr(pos, endPos + 1 - pos), TYPE_COMMENT);
                tokens.push_back(preText);
                tokens.push_back(commentTag);
                lastPos = endPos;
                pos = endPos + 1;
                continue;
            }

            if(isTagName(rawString, pos))
            {
                std::string tagName = getName(rawString, pos);
                int endPos = findTagEnd(rawString, pos);
                if(checkEmpty(endPos))
                    break;
                Token preText(rawString.substr(lastPos + 1, pos - lastPos - 1), TYPE_TEXT),
                      openTag(rawString.substr(pos, endPos + 1 - pos), TYPE_TAG);
                tokens.push_back(preText);
                tokens.push_back(openTag);

                // <script> xxxxxxxxxx </script>
                // .pos   .endPos      .pairPos.pairEndPos
                if(rawString[pos + 1] != '/' && isSpecialTag(tagName))
                {
                    // No closeTag
                    int pairPos = findSpecialPair(rawString, tagName, endPos + 1),
                        pairEndPos = findTagEnd(rawString, pairPos);
                    if(checkEmpty(pairPos) || checkEmpty(pairEndPos))
                        break;
                    Token inText(rawString.substr(endPos + 1, pairPos - endPos - 1), TYPE_TEXT),
                          closeTag(rawString.substr(pairPos, pairEndPos + 1 - pairPos), TYPE_TAG);
                    tokens.push_back(inText);
                    tokens.push_back(closeTag);

                    lastPos = pairEndPos;
                    pos = lastPos + 1;
                }  
                else
                {
                    lastPos = endPos;
                    pos = lastPos + 1;
                }
                continue;
            }
        }
        pos++;
    }
    Token lastToken(rawString.substr(lastPos + 1, strLen - lastPos - 1), TYPE_TEXT);
    tokens.push_back(lastToken);
    return tokens;
}