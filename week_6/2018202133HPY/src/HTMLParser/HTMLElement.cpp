#include "HTMLElement.hpp"

#include <exception>
#include <functional>
#include <regex>

#include "HTMLSpecialDefinition.hpp"

namespace cowr {

using Selector = std::function<bool(HTMLTagElement*)>;

std::unique_ptr<HTMLElement> HTMLElement::make_unique_from_token(HTMLNonEmptyTagElement* parent, HTMLTokenBase* ptoken)
{
    // std::cout << ptoken->toString() << std::endl;
    if (auto ptext = dynamic_cast<HTMLTextToken*>(ptoken); ptext) {
        return std::make_unique<HTMLTextElement>(parent, ptext->getValue());
    } else if (auto pcomment = dynamic_cast<HTMLCommentToken*>(ptoken); pcomment) {
        return std::make_unique<HTMLCommentElement>(parent, pcomment->getValue());
    } else if (auto punknown = dynamic_cast<HTMLUnknownToken*>(ptoken); punknown) {
        return std::make_unique<HTMLUnknownElement>(parent, punknown->getValue());
    } else if (auto ptag = dynamic_cast<HTMLTagToken*>(ptoken); ptag) {
        if (ptag->isClose()) {
            throw std::invalid_argument("Unexpected close tag");
        } else {
            if (HTMLSpecialDefinition::isEmptyElement(ptag->getValue())) {
                return std::make_unique<HTMLTagElement>(parent, ptag->getValue(), ptag->getAttr());
            } else {
                return std::make_unique<HTMLNonEmptyTagElement>(parent, ptag->getValue(), ptag->getAttr());
            }
        }
    } else {
        throw std::invalid_argument("Unexpected argument type: " + getClassName(ptoken));
    }
}

std::ostream& operator<<(std::ostream& os, HTMLElement& element)
{
    if (auto ptag = dynamic_cast<HTMLNonEmptyTagElement*>(&element); ptag != nullptr) {
        return os << ptag->HTMLTagElement::to_string(0, false);
    } else {
        return os << element.to_string(0, false);
    }
    return os;
}

inline Selector CompileSelector(std::string selector)
{
    static auto GenerateTagSelector = [](Selector selector, std::string tag) {
        return [selector, tag](HTMLTagElement* ptag) {
            return ptag->getTag() == tag && selector(ptag);
        };
    };

    static auto GenerateIDSelector = [](Selector selector, std::string id) {
        return [selector, id](HTMLTagElement* ptag) {
            return ptag->getAttr().getAttr("id") == id && selector(ptag);
        };
    };

    static auto GenerateClassSelector = [](Selector selector, std::string classname) {
        return [selector, classname](HTMLTagElement* ptag) {
            return ptag->getAttr().haveClass(classname) && selector(ptag);
        };
    };

    static auto GenerateAttrSelector = [](Selector selector, std::string attr_selector) {
        Selector ret;

        std::string attr_name, attr_val;

        int pos = attr_selector.find_first_of("!=$");

        attr_name = attr_selector.substr(0, pos);

        if (pos == std::string::npos) {
            ret = [attr_name, selector](HTMLTagElement* ptag) {
                return ptag->getAttr().haveAttr(attr_name) && selector(ptag);
            };
        } else {
            int val_start = attr_selector.find_first_of("'\"");
            int val_end = attr_selector.find_first_of(attr_selector[val_start], val_start + 1);
            attr_val = attr_selector.substr(val_start + 1, val_end - val_start - 1);

            if (attr_selector[pos] == '$') {
                ret = [attr_name, attr_val, selector](HTMLTagElement* ptag) {
                    auto val = ptag->getAttr().getAttr(attr_name);
                    if (val.length() < attr_val.length() || val.substr(val.length() - attr_val.length(), attr_val.length()) != attr_val) {
                        return false;
                    } else
                        return selector(ptag);
                };
            } else if (attr_selector[pos] == '!') {
                ret = [attr_name, attr_val, selector](HTMLTagElement* ptag) {
                    auto val = ptag->getAttr().getAttr(attr_name);
                    return val != attr_val && selector(ptag);
                };
            } else {
                ret = [attr_name, attr_val, selector](HTMLTagElement* ptag) {
                    auto val = ptag->getAttr().getAttr(attr_name);
                    return val == attr_val && selector(ptag);
                };
            }
        }

        return ret;
    };

    Selector ret = [](HTMLTagElement*) { return true; };

    size_t start_pos = selector.find_first_of(".*[");
    auto tag = selector.substr(0, start_pos);

    if (tag.length() == 0 || tag == "*") {
        ;
    } else {
        ret = GenerateTagSelector(ret, tag);
    }

    if (start_pos != std::string::npos) {

        selector = selector.substr(start_pos);

        std::regex re(R"RE(\.[^.\[#]*|#[^.\[#]*|\[\S[^=\]]*(=('[^']*'|"[^"]*"|)|)\])RE");

        auto selectors_begin = std::sregex_iterator(selector.begin(), selector.end(), re);
        auto selectors_end = std::sregex_iterator();

        for (std::sregex_iterator i = selectors_begin; i != selectors_end; ++i) {
            std::smatch match = *i;
            std::string match_str = match.str();
            // std::cout << match_str << '\n';

            if (match_str[0] == '.')
                ret = GenerateClassSelector(ret, match_str.substr(1));
            else if (match_str[0] == '#')
                ret = GenerateIDSelector(ret, match_str.substr(1));
            else
                ret = GenerateAttrSelector(ret, match_str.substr(1, match_str.length() - 2));
        }
    }
    return ret;
}

inline void FindElementBySelector(
    HTMLTagElement* element,
    std::vector<HTMLTagElement*>& list,
    Selector& compiled_selector)
{
    if (element == nullptr)
        return;

    if (compiled_selector(element))
        list.push_back(element);

    if (auto ptag = dynamic_cast<HTMLNonEmptyTagElement*>(element); ptag != nullptr) {
        for (auto&& child : *ptag) {
            FindElementBySelector(
                dynamic_cast<HTMLTagElement*>(child.get()),
                list,
                compiled_selector);
        }
    }
}

HTMLElementList HTMLNonEmptyTagElement::$(std::string selector)
{
    auto compiled_selector = CompileSelector(selector);
    std::vector<HTMLTagElement*> list;
    FindElementBySelector(this, list, compiled_selector);

    return HTMLElementList(list.begin(), list.end());
}

}
