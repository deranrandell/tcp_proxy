#include "include/TcpProxy.h"
#include "include/Logger.h"
#include "include/Config.h"
#include <iostream>

int main(int argc, char *argv[])
{
    try
    {
        Logger::init();

        // Load configuration from the INI file
        Config::instance().load_from_file("config.ini");

        Logger::get_logger()->info("Starting TCP Proxy...");

        TcpProxy proxy(Config::instance().get_source_ip(),
                       Config::instance().get_source_port(),
                       Config::instance().get_dest_ip(),
                       Config::instance().get_dest_port());
        proxy.start();
    }
    catch (const std::exception &e)
    {
        Logger::get_logger()->error("Application error: {}", e.what());
    }
    return 0;
}
