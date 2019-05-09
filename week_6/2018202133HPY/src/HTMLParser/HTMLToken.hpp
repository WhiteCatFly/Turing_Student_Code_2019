#ifndef _COWR_HTMLPARSER_HTMLToken

#define _COWR_HTMLPARSER_HTMLToken

#include <iostream>
#include <string>
#include <vector>

#ifdef __GNUC__

#include <cxxabi.h>

#endif

#include "HTMLTagAttr.hpp"

namespace cowr {

class HTMLTokenBase {
protected:
    std::string value;
    HTMLTokenBase() = default;
    HTMLTokenBase(std::string value)
        : value { value }
    {
    }

public:
    virtual ~HTMLTokenBase() = default;

    std::string getValue()
    {
        return value;
    }

    virtual std::string toString() const
    {
        return "[\"" + getClassName(this) + "\" \"" + escape_string(value) + "\"]";
    }
};

class HTMLTextToken : public HTMLTokenBase {
public:
    HTMLTextToken() = default;
    HTMLTextToken(std::string value)
        : HTMLTokenBase { value }
    {
    }
};

class HTMLCommentToken : public HTMLTokenBase {
public:
    HTMLCommentToken() = default;
    HTMLCommentToken(std::string value)
        : HTMLTokenBase { value }
    {
    }
};

class HTMLUnknownToken : public HTMLTokenBase {
public:
    HTMLUnknownToken() = default;
    HTMLUnknownToken(std::string value)
        : HTMLTokenBase { value }
    {
    }
};

class HTMLTagToken : public HTMLTokenBase {
protected:
    bool close_tag;
    HTMLTagAttr attr;

public:
    HTMLTagToken() = default;
    HTMLTagToken(std::string value)
        : HTMLTokenBase { value }
        , close_tag(false)
    {
    }

    HTMLTagToken(std::string value, HTMLTagAttr attr)
        : HTMLTokenBase { value }
        , attr(attr)
        , close_tag(false)
    {
    }

    HTMLTagToken(std::string value, HTMLTagAttr attr, bool close_tag)
        : HTMLTokenBase { value }
        , attr(attr)
        , close_tag(close_tag)
    {
    }

    HTMLTagToken(std::string value, HTMLTagAttr&& attr)
        : HTMLTokenBase { value }
        , attr(std::move(attr))
    {
    }

    auto getAttr() const
    {
        return attr;
    }

    virtual std::string toString() const
    {
        return "[\"" + getClassName(this) + "\" \"" + escape_string(value) + "\" " + (close_tag ? "close " : "") + attr.toString() + "]";
    }

    bool isClose() const
    {
        return close_tag;
    }
};

}

#endif
