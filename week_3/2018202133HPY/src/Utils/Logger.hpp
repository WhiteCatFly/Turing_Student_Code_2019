#ifndef _COWR_UTILS_LOGGER

#define _COWR_UTILS_LOGGER

#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <typeinfo>
#include <vector>

#include <sys/ioctl.h>
#include <sys/types.h>

#include "termutil.hpp"

namespace cowr {

class Logger {
public:
    enum {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    typedef std::function<std::string(bool, int, std::string)> Formatter;

    static std::string defaultFormatter(bool useColor, int level, std::string msg);

    struct Message {
        int level;
        std::string msg;

        Message()
            : level(DEBUG) {};
        Message(int level, std::string msg)
            : level(level)
            , msg(msg)
        {
        }
    };

    class Handler {
    protected:
        int level;
        Formatter formatter;

    public:
        Handler()
            : level(INFO)
            , formatter(defaultFormatter)
        {
        }

        virtual ~Handler() {}

        virtual Handler& setLevel(int level)
        {
            this->level = level;
            return *this;
        }

        virtual Handler& setFormatter(const Formatter& formatter)
        {
            this->formatter = formatter;
            return *this;
        }

        virtual Handler& setFormatter(Formatter&& formatter)
        {
            this->formatter = formatter;
            return *this;
        }

        virtual Handler& write(Message msg) = 0;

        virtual Handler& operator<<(Message msg)
        {
            return write(msg);
        }
    };

private:
    Logger() {};

    std::vector<std::shared_ptr<Handler>> handlers;

    mutable std::recursive_mutex lock;

public:
    static Logger& getInstance()
    {
        static std::unique_ptr<Logger> pglobal_logger;

        if (pglobal_logger == nullptr)
            pglobal_logger = std::unique_ptr<Logger>(new Logger);

        return *pglobal_logger;
    }

    Logger& addHandler(std::shared_ptr<Handler> handler)
    {
        std::unique_lock lock_this { lock };

        handlers.push_back(handler);
        return *this;
    }

    Logger& operator<<(Message msg)
    {
        std::unique_lock lock_this { lock };

        for (auto phandler : handlers) {
            (*phandler) << msg;
        }

        return *this;
    }

    Logger& debug(std::string msg)
    {
        (*this) << Message(DEBUG, msg);
        return *this;
    }

    Logger& info(std::string msg)
    {
        (*this) << Message(INFO, msg);
        return *this;
    }

    Logger& warning(std::string msg)
    {
        (*this) << Message(WARNING, msg);
        return *this;
    }

    Logger& error(std::string msg)
    {
        (*this) << Message(ERROR, msg);
        return *this;
    }

    Logger& critical(std::string msg)
    {
        (*this) << Message(CRITICAL, msg);
        return *this;
    }
};

class ostreamHandler : public Logger::Handler {
    bool color_enabled;
    std::shared_ptr<std::ostream> pstream;

public:
    ostreamHandler(std::ostream* stream, bool use_color = false, bool owns = true)
        : pstream(stream, [owns](std::ostream* stream) {
            if (owns) {
                delete stream;
            }
        })
        , color_enabled(use_color)
    {
    }

    ostreamHandler(std::shared_ptr<std::ostream> pstream, bool use_color)
        : pstream(pstream)
        , color_enabled(use_color)
    {
    }

    virtual Logger::Handler& write(Logger::Message msg) override
    {
        if (msg.level >= level) {

            std::string output = formatter(color_enabled, msg.level, msg.msg);

            if (auto _ = dynamic_cast<std::ofstream*>((std::ostream*)(pstream.get())); !_) {
                struct winsize ws;

                ioctl(1, TIOCGWINSZ, &ws);

                int columns = ws.ws_col;

                if (output.size() > columns) {
                    output = output.substr(0, columns - 3) + "...";
                }
            }

            (*pstream) << output << std::endl;
        }
        return *this;
    }
};

}

#endif
