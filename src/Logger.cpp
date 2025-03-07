#include "Logger.h"

std::shared_ptr<spdlog::logger> logger;

void Logger::init()
{
    if (!logger)
    {
        logger = spdlog::stdout_color_mt("tcp_proxy");
        spdlog::set_level(spdlog::level::info); // Set default log level
    }
}

std::shared_ptr<spdlog::logger> Logger::get_logger()
{
    return logger;
}
