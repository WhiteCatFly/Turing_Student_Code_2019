#ifndef _CRAW_UTILS_CONFIG

#define _CRAW_UTILS_CONFIG

#include <fstream>
#include <map>
#include <memory>
#include <string>

#include "Logger.hpp"
#include "trim.hpp"

namespace cowr {

class Config {
public:
    typedef std::map<std::string, std::string> Section;

    static Config& getInstance()
    {
        static std::unique_ptr<Config> pglobal_config;

        if (pglobal_config == nullptr)
            pglobal_config = std::unique_ptr<Config>(new Config);

        return *pglobal_config;
    }

private:
    std::map<std::string, Section> data;

    Config()
    {
        parseFromFile("config.ini");
    }

public:
    void parseFromFile(std::string path)
    {
        std::ifstream config_file { path };

        std::string line;
        std::string section_name = "Default";

        while (std::getline(config_file, line)) {
            trim(line);

            if (line == "")
                continue;

            if (line[0] == '[') {
                section_name = line.substr(1, line.find_last_not_of(" \t]"));
            } else {
                std::string key, value;
                key = line.substr(0, line.find_first_of("="));
                value = line.substr(line.find_first_of("=") + 1);

                data[section_name][key] = value;
            }
        }

        Logger::getInstance().info("Config readed from " + path);
    }

    auto begin()
    {
        return data.begin();
    }

    auto end()
    {
        return data.end();
    }

    operator std::map<std::string, Section>()
    {
        return data;
    }

    auto operator[](std::string name)
    {
        return data[name];
    }
};
}

#endif
