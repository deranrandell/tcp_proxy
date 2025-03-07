#include "Config.h"
#include <ini.h>
#include <stdexcept>
#include <iostream>

Config &Config::instance()
{
    static Config config;
    return config;
}

const std::string &Config::get_source_ip() const
{
    return source_ip_;
}

uint16_t Config::get_source_port() const
{
    return source_port_;
}

const std::string &Config::get_dest_ip() const
{
    return dest_ip_;
}

uint16_t Config::get_dest_port() const
{
    return dest_port_;
}

static int ini_callback(void *user, const char *section, const char *name, const char *value)
{
    Config *config = static_cast<Config *>(user);

    // Read source IP and port
    if (strcmp(section, "source") == 0)
    {
        if (strcmp(name, "ip") == 0)
        {
            config->source_ip_ = value;
        }
        else if (strcmp(name, "port") == 0)
        {
            config->source_port_ = static_cast<uint16_t>(std::stoi(value));
        }
    }
    // Read destination IP and port
    else if (strcmp(section, "destination") == 0)
    {
        if (strcmp(name, "ip") == 0)
        {
            config->dest_ip_ = value;
        }
        else if (strcmp(name, "port") == 0)
        {
            config->dest_port_ = static_cast<uint16_t>(std::stoi(value));
        }
    }

    return 1; // Continue processing
}

void Config::load_from_file(const std::string &file_path)
{
    int result = ini_parse(file_path.c_str(), ini_callback, this);
    if (result < 0)
    {
        throw std::runtime_error("Unable to parse the config file: " + file_path);
    }
}
