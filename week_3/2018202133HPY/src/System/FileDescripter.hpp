#ifndef _COWR_SYSTEM_FILEDESCRIPTER

#define _COWR_SYSTEM_FILEDESCRIPTER

#include <unistd.h>

#include "../Utils/Exceptions.hpp"

namespace cowr {

class FileDecscripter {
protected:
    enum State {
        Okey,
        Error
    };

    int fd;
    int state;

public:
    FileDecscripter()
        : fd(-1)
        , state(State::Error)
    {
    }

    virtual ~FileDecscripter()
    {
        ;
    }

    virtual ssize_t write(const void* buffer, size_t count)
    {
        if (state == Error) {
            ;
        }
    }
};

}

#endif
