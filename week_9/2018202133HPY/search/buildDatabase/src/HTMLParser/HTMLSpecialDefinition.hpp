#ifndef _COWR_HTMLPARSER_HTMLSPECIALDEFINITION

#define _COWR_HTMLPARSER_HTMLSPECIALDEFINITION

#include <algorithm>
#include <string>
#include <vector>

class HTMLSpecialDefinition {
    inline static std::vector<std::string> raw_text_tags = {
        "title",
        "textarea",
        "script",
        "style"
    };

    inline static std::vector<std::string> empty_elements = {
        "area",
        "base",
        "br",
        "col",
        "embed",
        "hr",
        "img",
        "input",
        "keygen",
        "link",
        "meta",
        "param",
        "source",
        "track",
        "wbr"
    };

    inline static std::vector<std::string> block_elements = {
        "address",
        "article",
        "aside",
        "blockquote",
        "details",
        "dialog",
        "dd",
        "div",
        "dl",
        "dt",
        "fieldset",
        "figcaption",
        "figure",
        "footer",
        "form",
        "h1", "h2", "h3", "h4", "h5", "h6",
        "header",
        "hgroup",
        "hr",
        "li",
        "main",
        "nav",
        "ol",
        "p",
        "pre",
        "section",
        "table",
        "ul"
    };

public:
    static bool isRawTextTag(std::string str)
    {
        return std::find(raw_text_tags.begin(), raw_text_tags.end(), str) != raw_text_tags.end();
    }

    static bool isEmptyElement(std::string str)
    {
        return std::find(empty_elements.begin(), empty_elements.end(), str) != empty_elements.end();
    }

    static bool isBlockElement(std::string str)
    {
        return std::find(block_elements.begin(), block_elements.end(), str) != block_elements.end();
    }
};

#endif
