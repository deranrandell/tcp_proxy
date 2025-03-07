#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <ini.h>

class Config
{
public:
    static Config &instance();

    // Getters for the configuration values
    const std::string &get_source_ip() const;
    uint16_t get_source_port() const;
    const std::string &get_dest_ip() const;
    uint16_t get_dest_port() const;

    // Loads configuration from the .ini file
    void load_from_file(const std::string &file_path);

private:
    Config() = default;

    std::string source_ip_;
    uint16_t source_port_;
    std::string dest_ip_;
    uint16_t dest_port_;
};

#endif // CONFIG_H
