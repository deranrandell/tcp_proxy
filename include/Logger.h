
#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>

class Logger
{
public:
    static void init();
    static std::shared_ptr<spdlog::logger> get_logger();
};

#endif // LOGGER_H
