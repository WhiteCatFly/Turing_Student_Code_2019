#ifndef _COWR_HTMLPARSER_HTMLELEMENT
#define _COWR_HTMLPARSER_HTMLELEMENT

#include <memory>
#include <string>
#include <vector>

#include "../Utils/termutil.hpp"
#include "HTMLToken.hpp"

namespace cowr {

class HTMLNonEmptyTagElement;

class HTMLElement {
protected:
    HTMLNonEmptyTagElement* parent;

public:
    HTMLElement(HTMLNonEmptyTagElement* parent)
        : parent(parent)
    {
    }

    virtual ~HTMLElement() = default;

    virtual std::string to_string(int indent, bool color) const = 0;

    virtual std::string toColorfulString() const
    {
        return to_string(0, true);
    }

    virtual std::string innerText() const = 0;

    virtual std::string toString() const
    {
        return to_string(0, false);
    }

    HTMLNonEmptyTagElement* getParent()
    {
        return parent;
    }

    static std::unique_ptr<HTMLElement> make_unique_from_token(HTMLNonEmptyTagElement*, HTMLTokenBase*);
};

class HTMLElementList {
    std::vector<HTMLElement*> elements;

public:
    template <typename... Arg>
    HTMLElementList(Arg&&... arg)
        : elements(arg...)
    {
    }

#define FORWARD_FUNCTION(object, func)            \
    template <typename... Arg>                    \
    decltype(auto) func(Arg&&... arg)             \
    {                                             \
        return object.func(std::forward(arg)...); \
    }

    FORWARD_FUNCTION(elements, begin)
    FORWARD_FUNCTION(elements, end)
    FORWARD_FUNCTION(elements, front)
    FORWARD_FUNCTION(elements, back)
    FORWARD_FUNCTION(elements, size)

#undef FORWARD_FUNCTION
};

class HTMLTextElementBase : public HTMLElement {
protected:
    std::string text;

public:
    HTMLTextElementBase(HTMLNonEmptyTagElement* parent, std::string text)
        : HTMLElement(parent)
        , text(text)
    {
    }

    virtual std::string innerText() const override
    {
        return "";
    }

    virtual std::string to_string(int indent, bool color) const override = 0;
};

class HTMLTextElement : public HTMLTextElementBase {
public:
    HTMLTextElement(HTMLNonEmptyTagElement* parent, std::string text)
        : HTMLTextElementBase(parent, text)
    {
    }

    virtual std::string to_string(int indent, bool color) const override
    {
        std::stringstream buffer;

        while (indent)
            buffer << ' ', indent--;

        buffer << "[";

        buffer << "(" << getClassName(this) << ")";

        buffer << " \"" << escape_string(text) << "\"]";

        return buffer.str();
    }

    virtual std::string innerText() const override
    {
        return text;
    }
};

class HTMLCommentElement : public HTMLTextElementBase {
public:
    HTMLCommentElement(HTMLNonEmptyTagElement* parent, std::string text)
        : HTMLTextElementBase(parent, text)
    {
    }

    virtual std::string to_string(int indent, bool color) const override
    {
        std::stringstream buffer;

        while (indent)
            buffer << ' ', indent--;

        buffer << "[";

        if (color)
            buffer << TermUtil::setForeGroundColor(TermUtil::GREEN);
        buffer << "(" << getClassName(this) << ")";
        if (color)
            buffer << TermUtil::resetAttr();

        buffer << " \"" << escape_string(text) << "\"]";

        return buffer.str();
    }
};

class HTMLUnknownElement : public HTMLTextElementBase {
public:
    HTMLUnknownElement(HTMLNonEmptyTagElement* parent, std::string text)
        : HTMLTextElementBase(parent, text)
    {
    }

    virtual std::string to_string(int indent, bool color) const override
    {
        std::stringstream buffer;

        while (indent)
            buffer << ' ', indent--;

        buffer << "[";

        if (color)
            buffer << TermUtil::setForeGroundColor(TermUtil::RED);
        buffer << "(" << getClassName(this) << ")";
        if (color)
            buffer << TermUtil::resetAttr();

        buffer << " \"" << escape_string(text) << "\"]";

        return buffer.str();
    }
};

class HTMLTagElement : public HTMLElement {
protected:
    std::string tag;
    HTMLTagAttr attr;

public:
    HTMLTagElement(HTMLNonEmptyTagElement* parent, std::string tag, HTMLTagAttr attr)
        : HTMLElement(parent)
        , tag(tag)
        , attr(attr)
    {
        ;
    }

    std::string getTag()
    {
        return tag;
    }

    HTMLTagAttr& getAttr()
    {
        return attr;
    }

    virtual std::string to_string(int indent, bool color) const override
    {
        std::stringstream buffer;

        while (indent)
            buffer << ' ', indent--;

        buffer << "[(" << getClassName(this) << ") " << tag;

        if (attr.size())
            buffer << " " << attr.toString();

        buffer << "]";

        return buffer.str();
    }

    virtual std::string innerText() const override
    {
        return tag == "br" ? "\n" : "";
    }
};

class HTMLNonEmptyTagElement : public HTMLTagElement {
protected:
    std::vector<std::unique_ptr<HTMLElement>> childs;

public:
    HTMLNonEmptyTagElement(HTMLNonEmptyTagElement* parent, std::string tag, HTMLTagAttr attr)
        : HTMLTagElement(parent, tag, attr)
    {
    }

    HTMLElement* addChild(std::unique_ptr<HTMLElement>&& child)
    {
        childs.push_back(std::move(child));
        return childs.back().get();
    }

    auto begin()
    {
        return childs.begin();
    }

    auto end()
    {
        return childs.end();
    }

    virtual std::string innerText() const override
    {
        std::stringstream buffer;

        for (auto&& child : childs) {
            buffer << child->innerText();
        }

        return buffer.str();
    }

    virtual std::string to_string(int indent, bool color) const override
    {
        std::stringstream buffer;

        buffer << HTMLTagElement::to_string(indent, color);

        for (auto&& child : childs) {
            buffer << "\n";
            buffer << child->to_string(indent + 2, color);
        }

        return buffer.str();
    }

    HTMLElementList $(std::string);
};

class HTMLDocument : public HTMLNonEmptyTagElement {
public:
    HTMLDocument()
        : HTMLNonEmptyTagElement(nullptr, "!DOCUMENT", HTMLTagAttr())
    {
    }
};

std::ostream& operator<<(std::ostream& os, HTMLElement& element);

}

#endif
