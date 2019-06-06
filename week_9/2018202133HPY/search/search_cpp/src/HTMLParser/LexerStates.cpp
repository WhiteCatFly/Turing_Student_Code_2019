#include "LexerStates.hpp"

#include <cctype>

#include "../Utils/util.hpp"
#include "HTMLSpecialDefinition.hpp"

namespace cowr {

// template <typename Type, typename... Arg>
// std::unique_ptr<Type> make_unique_and_emplace(Arg&&... arg)
// {
//     return std::unique_ptr<Type>(&((new Type)->emplace(std::forward(arg)...)));
// }

//FIXME

template <typename Type, typename... Arg>
std::unique_ptr<Type> make_unique_and_emplace(Arg&&... arg)
{
    return std::unique_ptr<Type> {
        dynamic_cast<std::remove_reference_t<Type>*>(
            &((new Type)->emplace(
                std::forward<std::remove_reference_t<Arg>>(arg)...)))
    };
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerEmptyState::nextState(char ch)
{
    if (ch == '<') {
        auto node = data.rdbuf()->in_avail() > 0 ? std::make_unique<HTMLTextToken>(data.str()) : nullptr;
        data = std::stringstream();

        data << ch;

        return std::make_tuple(
            make_unique_and_emplace<LexerLeftAngleBracket>(std::move(*this)),
            std::move(node),
            true);
    } else if (ch == EOF) {
        return std::make_tuple(
            std::make_unique<LexerEmptyState>(),
            data.rdbuf()->in_avail() > 0 ? std::make_unique<HTMLTextToken>(data.str()) : nullptr,
            true);
    } else {
        data << ch;
        return std::make_tuple(
            make_unique_and_emplace<LexerEmptyState>(std::move(*this)),
            nullptr,
            true);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerLeftAngleBracket::nextState(char ch)
{
    if (ch == '!') {
        data << ch;
        return std::make_tuple(
            make_unique_and_emplace<LexerLeftAngleBracketAndExclamation>(std::move(*this)),
            nullptr,
            true);
    } else if (ch == '/') {
        data << ch;
        return std::make_tuple(
            make_unique_and_emplace<LexerLeftAngleBracketAndSlash>(std::move(*this)),
            nullptr,
            true);
    } else if (ch == '?') {
        data << ch;
        return std::make_tuple(
            make_unique_and_emplace<LexerUnknownEndsWithRightAngleBracket>(std::move(*this)),
            nullptr,
            true);
    } else if (isalpha(ch)) {
        if (isupper(ch))
            ch = tolower(ch);

        data = std::stringstream();

        data << ch;

        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadName>(std::move(*this)),
            nullptr,
            true);
    } else {
        data << ch;
        return std::make_tuple(
            make_unique_and_emplace<LexerEmptyState>(std::move(*this)),
            nullptr,
            true);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerLeftAngleBracketAndSlash::nextState(char ch)
{
    if (isalpha(ch)) {
        //TODO close mark

        // clear data
        data = std::stringstream();
        data << ch;

        auto next_state = make_unique_and_emplace<LexerTagReadName>(std::move(*this));
        next_state->setCloseTag(true);

        return std::make_tuple(
            std::move(next_state),
            nullptr,
            true);
    } else {
        return make_unique_and_emplace<LexerUnknownEndsWithRightAngleBracket>(std::move(*this))->nextState(ch);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerLeftAngleBracketAndExclamation::nextState(char ch)
{
    if (ch == '-') {
        data << ch;

        return std::make_tuple(
            make_unique_and_emplace<LexerLeftAngleBracketAndExclamationAndMinus>(std::move(*this)),
            nullptr,
            true);
    } else {
        return make_unique_and_emplace<LexerUnknownEndsWithRightAngleBracket>(std::move(*this))->nextState(ch);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerLeftAngleBracketAndExclamationAndMinus::nextState(char ch)
{
    if (ch == '-') {
        data << ch;

        return std::make_tuple(
            make_unique_and_emplace<LexerNormalComment>(std::move(*this)),
            nullptr,
            true);
    } else {
        return make_unique_and_emplace<LexerUnknownEndsWithRightAngleBracket>(std::move(*this))->nextState(ch);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerUnknownEndsWithRightAngleBracket::nextState(char ch)
{
    data << ch;

    if (ch == '>') {
        return std::make_tuple(
            std::make_unique<LexerEmptyState>(),
            std::make_unique<HTMLUnknownToken>(data.str()),
            true);
    } else {
        return std::make_tuple(
            make_unique_and_emplace<LexerUnknownEndsWithRightAngleBracket>(std::move(*this)),
            nullptr,
            true);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerNormalComment::nextState(char ch)
{
    data << ch;

    auto str = data.str();

    if (str.size() >= 3 && str.substr(str.length() - 3, 3) == "-->") {
        str = str.substr(0, str.length() - 3);

        return std::make_tuple(
            std::make_unique<LexerEmptyState>(),
            std::make_unique<HTMLCommentToken>(str),
            true);
    } else {
        return std::make_tuple(
            make_unique_and_emplace<LexerNormalComment>(std::move(*this)),
            nullptr,
            true);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerReadRawText::nextState(char ch)
{
    if (ch != '<') {
        data << ch;

        return std::make_tuple(
            make_unique_and_emplace<LexerReadRawText>(std::move(*this)),
            nullptr,
            true);
    } else {
        return make_unique_and_emplace<LexerReadRawText_ReadingTag>(std::move(*this))->nextState(ch);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerReadRawText_ReadingTag::nextState(char ch)
{
    if (tagbuffer.rdbuf()->in_avail() > 0 && ch == '<') {
        data << tagbuffer.str();

        return make_unique_and_emplace<LexerReadRawText>(std::move(*this))->nextState(ch);
    } else {
        std::string str = tagbuffer.str();

        if (isspace(ch) || ch == '>') {
            if (str == "</" + type) {
                std::unique_ptr<LexerStateBase> state = std::make_unique<LexerEmptyState>();

                for (auto x : str) {
                    auto [new_state, token, succeed] = state->nextState(x);

                    if (!succeed)
                        throw std::logic_error("Unexpected multi-tag at LexerReadRawText_ReadingTag::nextState");

                    state = std::move(new_state);
                }

                return std::make_tuple(
                    std::move(state),
                    std::make_unique<HTMLTextToken>(data.str()),
                    false);
            } else {
                data << tagbuffer.str() << ch;
                return std::make_tuple(
                    make_unique_and_emplace<LexerReadRawText>(std::move(*this)),
                    nullptr,
                    true);
            }
        } else {
            tagbuffer << ch;
            return std::make_tuple(
                make_unique_and_emplace<LexerReadRawText_ReadingTag>(std::move(*this)),
                nullptr,
                true);
        }
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerReadRawText_ReturnTag::nextState(char ch)
{
    std::cerr << "LexerReadRawText_ReturnTag::nextState : " << ch << std::endl;
    return std::make_tuple(
        std::make_unique<LexerEmptyState>(),
        std::move(LexerReadRawText_ReadingTag::token),
        true);
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerTagReadName::nextState(char ch)
{
    if (isblank(ch)) {
        LexerTagState::name = data.str();
        data = std::stringstream();

        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttr>(std::move(*this)),
            nullptr,
            true);
    } else if (ch == '>') {
        LexerTagState::name = data.str();
        data = std::stringstream();

        return make_unique_and_emplace<LexerTagReadAttr>(std::move(*this))->nextState(ch);
    } else {
        if (isupper(ch))
            ch = tolower(ch);

        data << ch;

        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadName>(std::move(*this)),
            nullptr,
            true);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerTagReadAttr::nextState(char ch)
{
    if (isblank(ch) || ch == '/') {
        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttr>(std::move(*this)),
            nullptr,
            true);
    } else if (ch == '>') {
        if (HTMLSpecialDefinition::isRawTextTag(LexerTagState::name) && !LexerTagState::close_tag) {
            auto state = std::make_unique<LexerReadRawText>();
            state->setType(LexerTagState::name);

            return std::make_tuple(
                std::move(state),
                std::make_unique<HTMLTagToken>(LexerTagState::name, LexerTagState::attr, LexerTagState::close_tag),
                true);
        } else {
            return std::make_tuple(
                std::make_unique<LexerEmptyState>(),
                std::make_unique<HTMLTagToken>(LexerTagState::name, LexerTagState::attr, LexerTagState::close_tag),
                true);
        }
    } else {
        if (isupper(ch))
            ch = tolower(ch);

        data << ch;

        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttrName>(std::move(*this)),
            nullptr,
            true);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerTagReadAttrName::nextState(char ch)
{
    if (ch == '=' || isblank(ch)) {
        LexerTagReadAttr::attr_name = data.str();
        data = std::stringstream();

        return make_unique_and_emplace<LexerTagReadAttrVal_WaitingEqualSign>(std::move(*this))->nextState(ch);
    } else if (ch == '/' || ch == '>') {
        LexerTagReadAttr::attr_name = data.str();
        data = std::stringstream();

        attr.addAttr(attr_name, "");

        return LexerTagReadAttr(std::move(*this)).nextState(ch);
    } else {
        if (isupper(ch))
            ch = tolower(ch);

        data << ch;

        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttrName>(std::move(*this)),
            nullptr,
            true);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerTagReadAttrVal_WaitingEqualSign::nextState(char ch)
{
    if (isspace(ch)) {
        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttrVal_WaitingEqualSign>(std::move(*this)),
            nullptr,
            true);
    } else {
        switch (data.str().length()) {
        case 0:
            if (ch == '=') {
                data << ch;
                return std::make_tuple(
                    make_unique_and_emplace<LexerTagReadAttrVal_WaitingEqualSign>(std::move(*this)),
                    nullptr,
                    true);
            } else {
                return make_unique_and_emplace<LexerTagReadAttr>(std::move(*this))->nextState(ch);
            }
            break;

        case 1:
            if (ch == '\'') {
                data = std::stringstream();
                return std::make_tuple(
                    make_unique_and_emplace<LexerTagReadAttrValWrappedBySingleQuote>(std::move(*this)),
                    nullptr,
                    true);
            } else if (ch == '"') {
                data = std::stringstream();
                return std::make_tuple(
                    make_unique_and_emplace<LexerTagReadAttrValWrappedByDoubleQuote>(std::move(*this)),
                    nullptr,
                    true);
            } else if (ch == '>') {
                attr.addAttr(attr_name, "");
                return make_unique_and_emplace<LexerTagReadAttr>(std::move(*this))->nextState(ch);
            } else {
                data = std::stringstream();
                data << ch;
                return std::make_tuple(
                    make_unique_and_emplace<LexerTagReadAttrValWrappedByNoQuote>(std::move(*this)),
                    nullptr,
                    true);
            }
            break;

        default:
            throw std::logic_error("Unexpected value data.str().length() of " + std::to_string(data.str().length()) + " at LexerTagReadAttrVal_WaitingEqualSign::nextState");
        }
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerTagReadAttrValWrappedByDoubleQuote::nextState(char ch)
{
    if (ch == '"') {
        attr_val = data.str();
        data = std::stringstream();

        attr.addAttr(attr_name, attr_val);

        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttr>(std::move(*this)),
            nullptr,
            true);
    } else {
        data << ch;
        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttrValWrappedByDoubleQuote>(std::move(*this)),
            nullptr,
            true);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerTagReadAttrValWrappedBySingleQuote::nextState(char ch)
{
    if (ch == '\'') {
        attr_val = data.str();
        data = std::stringstream();

        attr.addAttr(attr_name, attr_val);

        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttr>(std::move(*this)),
            nullptr,
            true);
    } else {
        data << ch;
        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttrValWrappedBySingleQuote>(std::move(*this)),
            nullptr,
            true);
    }
}

std::tuple<
    std::unique_ptr<LexerStateBase>,
    std::unique_ptr<HTMLTokenBase>,
    bool>
LexerTagReadAttrValWrappedByNoQuote::nextState(char ch)
{
    if (ch == '>' || isspace(ch)) {
        attr_val = data.str();
        data = std::stringstream();

        attr.addAttr(attr_name, attr_val);

        return make_unique_and_emplace<LexerTagReadAttr>(std::move(*this))->nextState(ch);
    } else {
        data << ch;
        return std::make_tuple(
            make_unique_and_emplace<LexerTagReadAttrValWrappedByNoQuote>(std::move(*this)),
            nullptr,
            true);
    }
}

}
