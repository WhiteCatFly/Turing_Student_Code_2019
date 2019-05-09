#ifndef _LEXER_H
#define _LEXER_H

#include <iostream>
#include <string>
#include <vector>

#include "Token.h"

std::vector<Token> getTokens(std::string rawString);

#endif