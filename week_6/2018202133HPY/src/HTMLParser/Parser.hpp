#ifndef _COWR_HTMLPARSER_PARSER

#define _COWR_HTMLPARSER_PARSER

// #include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>

#include "HTMLElement.hpp"
#include "Lexer.hpp"

namespace cowr {

class HTMLParser {
    HTMLLexer lexer;
    std::shared_ptr<HTMLDocument> pdocument;

public:
    HTMLParser()
        : pdocument(new HTMLDocument)
    {
    }

    HTMLParser(std::string html)
        : HTMLParser()
    {
        lexer << html;
    }

    // HTMLParser(std::filesystem::path path)
    //     : HTMLParser()
    // {
    //     std::ifstream input(path);

    //     char ch;

    //     while (input.get(ch))
    //         lexer << ch;
    // }

    HTMLParser(std::istream& os)
        : HTMLParser()
    {
        char ch;

        while (os.get(ch))
            lexer << ch;
    }

    HTMLParser(std::istream&& os)
        : HTMLParser()
    {
        char ch;

        while (os.get(ch))
            lexer << ch;
    }

    std::vector<std::unique_ptr<HTMLTokenBase>> lexOnly()
    {
        return lexer.lex();
    }

    std::shared_ptr<HTMLDocument> parse()
    {
        HTMLNonEmptyTagElement* now = pdocument.get();

        auto tokens = lexOnly();

        for (auto&& token : tokens) {
            auto ptoken = token.get();

            if (auto ptag = dynamic_cast<HTMLTagToken*>(ptoken); ptag && ptag->isClose()) {
                HTMLNonEmptyTagElement* next = now;

                while (next) {
                    if (next->getTag() == ptag->getValue()) {
                        break;
                    }
                    next = next->getParent();
                }

                if (next) {
                    now = next->getParent();

                    if (!next) {
                        DEBUG_THROW(std::logic_error, "Unexpected null parent");
                    }
                }
            } else {
                auto element_unique_ptr = HTMLElement::make_unique_from_token(now, token.get());
                auto pelement = now->addChild(std::move(element_unique_ptr));

                if (auto ptag = dynamic_cast<HTMLNonEmptyTagElement*>(pelement); ptag) {
                    now = ptag;
                }
            }
        }

        return pdocument;
    }

    template <typename T>
    HTMLParser& operator<<(T&& t)
    {
        lexer << t;
        return *this;
    }
};
}

#endif
