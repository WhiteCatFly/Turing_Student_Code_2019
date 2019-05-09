#include <libconfig.h++>
#include <iostream>
#include <string>
#include <iomanip>

#include "Config.h"

int initConfig(libconfig::Config &cfg)
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

std::string getStringConfig_(std::string configName, libconfig::Config &cfg)
{
    try
    {
        std::string ret = cfg.lookup(configName);
        return ret;
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
        std::cerr << "No '" << configName << "' setting in configuration file." << std::endl;
    }
    return "";
}

int getIntConfig_(std::string configName, libconfig::Config &cfg)
{
    try
    {
        int ret = cfg.lookup(configName);
        return ret;
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
        std::cerr << "No '" << configName << "' setting in configuration file." << std::endl;
    }
    return 0;
}


