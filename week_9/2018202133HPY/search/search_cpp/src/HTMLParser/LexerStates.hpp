#ifndef _COWR_HTMLPARSER_PARSERSTATES

#define _COWR_HTMLPARSER_PARSERSTATES

#include <memory>
#include <optional>
#include <sstream>
#include <tuple>
#include <utility>

#include "../Utils/util.hpp"
#include "HTMLToken.hpp"

namespace cowr {

class LexerStateBase {
protected:
    std::stringstream data;

public:
    LexerStateBase() = default;
    LexerStateBase(LexerStateBase&&) = default;
    virtual ~LexerStateBase() = default;
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) = 0;

    virtual LexerStateBase& emplace(LexerStateBase&& r)
    {
        data = std::move(r.data);

        return convertToReference(this);
    }
};

class LexerEmptyState : public LexerStateBase {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerLeftAngleBracket : public LexerStateBase {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerLeftAngleBracketAndSlash : public LexerStateBase {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerLeftAngleBracketAndExclamation : public LexerStateBase {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerLeftAngleBracketAndExclamationAndMinus : public LexerStateBase {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerUnknownEndsWithRightAngleBracket : public LexerStateBase {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerNormalComment : public LexerStateBase {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerReadRawText : public LexerStateBase {
protected:
    std::string type;

public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;

    virtual LexerStateBase& emplace(LexerStateBase&& r) override
    {
        LexerStateBase::emplace(std::move(r));

        if (LexerReadRawText* p = dynamic_cast<LexerReadRawText*>(&r); p != nullptr) {
            type = std::move(p->type);
        }

        return convertToReference(this);
    }

    void setType(std::string type)
    {
        LexerReadRawText::type = type;
    }
};

class LexerReadRawText_ReadingTag : public LexerReadRawText {
protected:
    std::stringstream tagbuffer;
    std::unique_ptr<LexerStateBase> now_state;
    std::unique_ptr<HTMLTokenBase> token;

public:
    LexerReadRawText_ReadingTag()
        : now_state(new LexerEmptyState())
    {
    }

    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;

    virtual LexerStateBase& emplace(LexerStateBase&& r) override
    {
        LexerReadRawText::emplace(std::move(r));

        if (LexerReadRawText_ReadingTag* p = dynamic_cast<LexerReadRawText_ReadingTag*>(&r); p != nullptr) {
            tagbuffer = std::move(p->tagbuffer);
            now_state = std::move(p->now_state);
            token = std::move(p->token);
        }

        return convertToReference(this);
    }
};

class LexerReadRawText_ReturnTag : public LexerReadRawText_ReadingTag {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerTagState : public LexerStateBase {
protected:
    bool close_tag = false;
    std::string name;
    HTMLTagAttr attr;

public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override = 0;

    virtual LexerStateBase& emplace(LexerStateBase&& r) override
    {
        LexerStateBase::emplace(std::move(r));

        if (auto* pr = dynamic_cast<LexerTagState*>(&r); pr != nullptr) {
            name = std::move(pr->name);
            attr = std::move(pr->attr);
            close_tag = pr->close_tag;
        }

        return convertToReference(this);
    }

    void setCloseTag(bool close_tag)
    {
        LexerTagState::close_tag = close_tag;
    }
};

class LexerTagReadName : public LexerTagState {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerTagReadAttr : public LexerTagState {
protected:
    std::string attr_name, attr_val;

public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;

    virtual LexerStateBase& emplace(LexerStateBase&& r) override
    {
        LexerTagState::emplace(std::move(r));

        if (auto* pr = dynamic_cast<LexerTagReadAttr*>(&r); pr != nullptr) {
            attr_name = std::move(pr->attr_name);
            attr_val = std::move(pr->attr_val);
        }

        return convertToReference(this);
    }
};

class LexerTagReadAttrName : public LexerTagReadAttr {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerTagReadAttrVal_WaitingEqualSign : public LexerTagReadAttr {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerTagReadAttrVal : public LexerTagReadAttr {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerTagReadAttrValWrappedBySingleQuote : public LexerTagReadAttr {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerTagReadAttrValWrappedByDoubleQuote : public LexerTagReadAttr {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

class LexerTagReadAttrValWrappedByNoQuote : public LexerTagReadAttr {
public:
    virtual std::tuple<
        std::unique_ptr<LexerStateBase>,
        std::unique_ptr<HTMLTokenBase>,
        bool>
    nextState(char ch) override;
};

}

#endif
