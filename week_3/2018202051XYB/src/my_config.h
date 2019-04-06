#ifndef _MY_CONFIG_H
#define _MY_CONFIG_H

#include <libconfig.h++>
#include <iostream>
#include <string>
#include <iomanip>

#define get_int_config(config_name) get_int_config_(#config_name, cfg)
#define get_string_config(config_name) get_string_config_(#config_name, cfg)

int config_init(libconfig::Config &cfg);
std::string get_string_config_(std::string config_name, libconfig::Config &cfg);
int get_int_config_(std::string config_name, libconfig::Config &cfg);

#endif