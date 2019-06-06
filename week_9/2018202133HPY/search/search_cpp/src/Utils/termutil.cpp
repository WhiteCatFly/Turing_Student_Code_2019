#include "termutil.hpp"

namespace cowr {

std::string to_string(const TermUtil::AnsiControlSequence& acs)
{
    return acs.toString();
}

std::ostream& operator<<(std::ostream& o, const TermUtil::AnsiControlSequence& acs)
{
    return o << acs.toString();
}

}
