#ifndef _COWR_EVENTLOOP_EVENT

#define _COWR_EVENTLOOP_EVENT

#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <random>

#include "../Utils/timeutil.hpp"

namespace cowr {

class Event {
    inline static std::mt19937_64 gen;

    uint64_t UUID_h, UUID_l;

public:
    millisecond_t time;
    std::function<void()> callback;

    Event(millisecond_t time, std::function<void()> callback)
        : time(time)
        , callback(callback)
        , UUID_h(gen())
        , UUID_l(gen())
    {
    }

    friend bool operator<(const Event& l, const Event& r)
    {
        if (l.time != r.time)
            return l.time < r.time;
        else if (l.UUID_h != r.UUID_h)
            return l.UUID_h < r.UUID_h;
        else
            return l.UUID_l < r.UUID_l;
    }

    friend bool operator==(const Event& l, const Event& r)
    {
        return l.UUID_l == r.UUID_l && l.UUID_h == r.UUID_h;
    }

    struct cmp_shared_ptr {
        bool operator()(const std::shared_ptr<Event>& l, const std::shared_ptr<Event>& r) const
        {
            if (l->time != r->time)
                return l->time < r->time;
            else if (l->UUID_h != r->UUID_h)
                return l->UUID_h < r->UUID_h;
            else
                return l->UUID_l < r->UUID_l;
        }
    };
};
}

#endif
