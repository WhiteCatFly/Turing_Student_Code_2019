#ifndef _CRAW_CONFIG

#define _CRAW_CONFIG

#include <fstream>
#include <map>
#include <string>

#include "trim.hpp"

class Config {
public:
    typedef std::map<std::string, std::string> Section;

    static Config& getConfig()
    {
        static Config global_config;
        return global_config;
    }

    static inline Config& global_config = getConfig();

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

#endif
