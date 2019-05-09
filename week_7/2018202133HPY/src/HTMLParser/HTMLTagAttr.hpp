#ifndef _COWR_HTMLPARSER_HTMLTAGATTR

#define _COWR_HTMLPARSER_HTMLTAGATTR

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../Utils/util.hpp"

namespace cowr {

class HTMLTagAttr {
public:
    using Attr = std::pair<std::string, std::string>;

private:
    std::set<std::string> classes;
    std::vector<Attr> attr_list;

public:
    auto begin()
    {
        return attr_list.begin();
    }

    auto begin() const
    {
        return attr_list.begin();
    }

    auto end()
    {
        return attr_list.end();
    }

    auto end() const
    {
        return attr_list.end();
    }

    auto size() const
    {
        return attr_list.size();
    }

    auto& addAttr(std::string name, std::string value)
    {
        auto pos = begin();

        for (auto end_pos = end(); pos != end_pos; pos++) {
            if (name == pos->first)
                break;
        }

        attr_list.emplace(pos, std::make_pair(name, value));

        if (name == "class") {
            int start = 0, end = value.find_first_of(" \v\t\n");

            do {
                std::string classname = value.substr(start, end - start);
                trim(classname);
                classes.insert(std::move(classname));

                start = value.find_first_not_of(" \v\t\n", end);
                end = value.find_first_of(" \v\t\n", start);
            } while (start < value.size());
        }

        return *this;
    }

    bool haveClass(std::string classname)
    {
        return classes.count(classname);
    }

    bool haveAttr(std::string name)
    {
        for (auto& pair : attr_list) {
            if (pair.first == name)
                return true;
        }

        return false;
    }

    std::string getAttr(std::string name)
    {
        for (auto& pair : attr_list) {
            if (pair.first == name)
                return pair.second;
        }

        return "";
    }

    std::string toString() const
    {
        std::stringstream buffer;

        for (auto&& attr : attr_list) {
            buffer << " ";
            buffer << attr.first;
            buffer << "=\"";
            buffer << escape_string(attr.second);
            buffer << '"';
        }

        buffer.get(); //Delete the first space (if any)

        return buffer.str();
    }
};

}

#endif
