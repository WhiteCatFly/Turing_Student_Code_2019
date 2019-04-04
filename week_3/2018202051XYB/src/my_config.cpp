#include <libconfig.h++>
#include <iostream>
#include <string>
#include <iomanip>

#include "my_config.h"

int config_init(libconfig::Config &cfg)
{
    try
    {
        cfg.readFile("config.cfg");
    }
    catch(const libconfig::FileIOException &fioex)
    {
        std::cerr << "I/O error while reading config file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch(const libconfig::ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                    << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

std::string get_string_config_(std::string config_name, libconfig::Config &cfg)
{
    try
    {
        std::string ret = cfg.lookup(config_name);
        return ret;
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
        std::cerr << "No '" << config_name << "' setting in configuration file." << std::endl;
    }
    return "";
}

int get_int_config_(std::string config_name, libconfig::Config &cfg)
{
    try
    {
        int ret = cfg.lookup(config_name);
        return ret;
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
        std::cerr << "No '" << config_name << "' setting in configuration file." << std::endl;
    }
    return 0;
}