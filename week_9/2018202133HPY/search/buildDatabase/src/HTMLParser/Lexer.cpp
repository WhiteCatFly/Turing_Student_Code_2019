#include "Lexer.hpp"

namespace cowr {

std::vector<std::unique_ptr<HTMLTokenBase>> HTMLLexer::lex()
{
    std::vector<std::unique_ptr<HTMLTokenBase>> ret, tmp;

    char ch;
    while (buffer.get(ch)) {
        bool succeed = false;

        while (!succeed) {
            auto [new_state, token, now_succeed] = now_state->nextState(ch);
            succeed = now_succeed;

            now_state = std::move(new_state);

            if (token) {
                tmp.push_back(std::move(token));
            }
        }
    }

    {
        bool succeed = false;

        while (!succeed) {
            auto [new_state, token, now_succeed] = now_state->nextState(EOF);
            succeed = now_succeed;

            now_state = std::move(new_state);

            if (token) {
                tmp.push_back(std::move(token));
            }
        }
    }

    {
        for (auto it = tmp.begin(), end = tmp.end(); it != end; it++) {
            auto& token = convertToReference(it->get());

            if (auto p_text_token = dynamic_cast<HTMLTextToken*>(&token); p_text_token != nullptr) {
                std::stringstream data;

                for (auto merge = it; merge != end; merge++) {
                    if (auto p_now = dynamic_cast<HTMLTextToken*>(merge->get()); p_now != nullptr) {
                        data << p_now->getValue();
                    } else {
                        merge--;
                        it = merge;
                        break;
                    }
                }

                if (data.rdbuf()->in_avail() > 0) {
                    auto str = data.str();
                    trim(str);

                    if (str.length())
                        ret.push_back(std::make_unique<HTMLTextToken>(str));
                }

            } else {
                ret.push_back(std::move(*it));
            }
        }
    }

    return ret;
}

}
