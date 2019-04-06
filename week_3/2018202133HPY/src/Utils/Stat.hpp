#ifndef _COWR_UTILS_STAT

#define _COWR_UTILS_STAT

#include <map>
#include <memory>
#include <mutex>
#include <thread>

#include "Logger.hpp"

namespace cowr {

class Stat {
protected:
    std::recursive_mutex lock;
    std::map<std::string, int> request_cnt;
    int header_counter, dropped_counter;

    Stat()
        : header_counter(0)
        , dropped_counter(0)
    {
        Logger::getInstance().info("Stat initialized");
    }

public:
    int queryRequest(const std::string& url)
    {
        std::unique_lock lock_this { lock };
        auto it = request_cnt.find(url);
        if (it == request_cnt.end())
            return 0;
        else
            return it->second;
    }

    int queryHeader()
    {
        std::unique_lock lock_this { lock };
        return header_counter;
    }

    void incRequest(const std::string& url)
    {
        std::unique_lock lock_this { lock };
        request_cnt[url]++;
    }

    void incHeaderCounter()
    {
        std::unique_lock lock_this { lock };
        header_counter++;
    }

    void incDroppedCounter()
    {
        std::unique_lock lock_this { lock };
        dropped_counter++;
    }

    static Stat& getInstance()
    {
        static std::unique_ptr<Stat> pglobal_stat;

        if (pglobal_stat == nullptr)
            pglobal_stat = std::unique_ptr<Stat>(new Stat);

        return *pglobal_stat;
    }
};

}

#endif
