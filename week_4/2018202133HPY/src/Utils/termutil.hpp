#ifndef _COWR_UTILS_TERMUTIL

#define _COWR_UTILS_TERMUTIL

#include <iostream>
#include <string>

namespace cowr {

class TermUtil {
public:
    struct AnsiControlSequence {
        virtual ~AnsiControlSequence() {};

        virtual std::string toString() const = 0;

        friend std::string to_string(const AnsiControlSequence& acs);

        friend std::ostream& operator<<(std::ostream& o, const AnsiControlSequence& acs);
    };

    struct ResetTermAttribute : public TermUtil::AnsiControlSequence {
        virtual std::string toString() const override
        {
            return "\033[0m";
        }
    };

private:
    struct ColorControlSequence : public TermUtil::AnsiControlSequence {

        int type, color;

        ColorControlSequence(int type, int color)
            : type(type)
            , color(color)
        {
        }

        virtual std::string toString() const override
        {
            return "\033[" + std::to_string(type + color) + "m";
        }
    };

public:
    enum {
        FOREGROUND = 30,
        BACKGROUND = 40
    };

    enum {
        BLACK = 0,
        RED = 1,
        GREEN = 2,
        YELLOW = 3,
        BLUE = 4,
        MAGENTA = 5,
        CYAN = 6,
        WHITE = 7
    };

    static ResetTermAttribute resetAttr()
    {
        return ResetTermAttribute();
    }

    static ColorControlSequence setColor(int type, int color)
    {
        return ColorControlSequence(type, color);
    }

    static ColorControlSequence setForeGroundColor(int color)
    {
        return ColorControlSequence(FOREGROUND, color);
    }

    static ColorControlSequence setBackGroundColor(int color)
    {
        return ColorControlSequence(BACKGROUND, color);
    }
};

}

#endif
