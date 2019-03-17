#ifndef _COWR_EXCEPTIONS

#define _COWR_EXCEPTIONS

#include <signal.h>

#include <exception>
#include <string>

class COWRBaseException : public std::exception {
public:
    virtual const char* what() const noexcept
    {
        return "cowr_base_exception";
    }
};

class FloatingPointException : public COWRBaseException {
public:
    virtual const char* what() const noexcept
    {
        return "floating_point_exception";
    }
};

class SegmentFaltException : public COWRBaseException {
public:
    virtual const char* what() const noexcept
    {
        return "segment_falt_exception";
    }
};

class BusErrorException : public COWRBaseException {
public:
    virtual const char* what() const noexcept
    {
        return "bus_error_exception";
    }
};

class __cowr_signal_init {
    static void UnblockSignal(int sig)
    {
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, sig);
        sigprocmask(SIG_UNBLOCK, &set, nullptr);
    }
    static void SignalExceptionHandler(int sig)
    {
        UnblockSignal(sig);

        switch (sig) {
        case SIGFPE:
            throw FloatingPointException();
        case SIGSEGV:
            throw SegmentFaltException();
        case SIGBUS:
            throw BusErrorException();
        }
    }

    inline static int _ = []() {
        signal(SIGFPE, SignalExceptionHandler);
        signal(SIGSEGV, SignalExceptionHandler);
        signal(SIGBUS, SignalExceptionHandler);

        signal(SIGPIPE, SIG_IGN);

        return 0;
    }();
};

class Error {
    std::string info;

public:
    Error(const char* info)
        : info(info)
    {
    }

    Error(std::string info)
        : info(info)
    {
    }

    Error(int err)
    {
        if (err)
            info = std::to_string(err);
    }

    virtual const char* what()
    {
        return info.c_str();
    }

    operator bool()
    {
        return info.size();
    }

    operator std::string()
    {
        return info;
    }
};

#endif
