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

public:
    static bool isRawTextTag(std::string str)
    {
        return std::find(raw_text_tags.begin(), raw_text_tags.end(), str) != raw_text_tags.end();
    }

    static bool isEmptyElement(std::string str)
    {
        return std::find(empty_elements.begin(), empty_elements.end(), str) != empty_elements.end();
    }
};

#endif
