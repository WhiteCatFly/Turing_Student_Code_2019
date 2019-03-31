#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <string>

#include "Crawler.hpp"
#include "EventLoop.hpp"
#include "Stat.hpp"
#include "URIHelper.hpp"

#include "Config.hpp"

inline Stat& global_stat = Stat::getStat();
inline Config& global_config = Config::getConfig();

int main(void)
{
    global_loop.start();

    global_stat.incRequest(getSavePath(global_config["Global"]["root"]));

    processURL(global_config["Global"]["root"]);

    global_loop.loop_until_done();

    return 0;
}
