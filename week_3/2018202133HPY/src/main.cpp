#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <string>

#include <typeinfo>

#include "Crawler.hpp"
#include "EventLoop/EventLoop.hpp"
#include "Utils/Config.hpp"
#include "Utils/Stat.hpp"
#include "Utils/URIHelper.hpp"
#include "Utils/termutil.hpp"

#include "Utils/Logger.hpp"

int main(void)
{
    cowr::Logger& global_logger = cowr::Logger::getInstance();

    global_logger.addHandler(std::shared_ptr<cowr::Logger::Handler>(&(
        (new cowr::ostreamHandler(&std::cout, true, false))->setLevel(cowr::Logger::INFO))));
    global_logger.addHandler(std::shared_ptr<cowr::Logger::Handler>(&(
        (new cowr::ostreamHandler(new std::ofstream("log.txt", std::ios::app)))->setLevel(cowr::Logger::DEBUG))));

    cowr::Stat& global_stat = cowr::Stat::getInstance();
    cowr::Config& global_config = cowr::Config::getInstance();
    cowr::EventLoop& global_loop = cowr::EventLoop::getInstance();

    global_stat.incRequest(getSavePath(global_config["Global"]["root"]));

    processURL(global_config["Global"]["root"]);

    global_loop.loop_until_done();

    return 0;
}
