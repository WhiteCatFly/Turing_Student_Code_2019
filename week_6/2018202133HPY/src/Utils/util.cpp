#include "util.hpp"

namespace cowr {

std::string escape_string(std::string str)
{
    std::stringstream buffer;

    for (auto ch : str) {
        switch (ch) {
        case '"':
            buffer << "\\\"";
            break;
        case '\\':
            buffer << "\\\\";
            break;
        case '\f':
            buffer << "\\f";
            break;
        case '\n':
            buffer << "\\n";
            break;
        case '\r':
            buffer << "\\r";
            break;
        case '\t':
            buffer << "\\t";
            break;
        case '\v':
            buffer << "\\v";
            break;
        default:
            buffer << ch;
            break;
        }
    }

    return buffer.str();
}

}
