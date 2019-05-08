#ifndef _CONFIG_H
#define _CONFIG_H

#include <libconfig.h++>
#include <iostream>
#include <string>
#include <iomanip>

#define getIntConfig(configName) getIntConfig_(#configName, cfg)
#define getStringConfig(configName) getStringConfig_(#configName, cfg)

int initConfig(libconfig::Config &cfg);
std::string getStringConfig_(std::string configName, libconfig::Config &cfg);
int getIntConfig_(std::string configName, libconfig::Config &cfg);

#endif