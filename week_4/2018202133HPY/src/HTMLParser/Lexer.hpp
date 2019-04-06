#ifndef _COWR_HTMLLexer_Lexer

#define _COWR_HTMLLexer_Lexer

#include <memory>
#include <sstream>
#include <vector>

#include "HTMLTagAttr.hpp"
#include "HTMLToken.hpp"
#include "LexerStates.hpp"

namespace cowr {

class HTMLLexer {
    std::stringstream buffer;

    std::unique_ptr<LexerStateBase> now_state;

public:
    HTMLLexer()
        : now_state(new LexerEmptyState)
    {
    }

    std::vector<std::unique_ptr<HTMLTokenBase>> lex();

    template <typename T>
    HTMLLexer& operator<<(T&& t)
    {
        buffer << t;
        return *this;
    }
};

}

#endif
