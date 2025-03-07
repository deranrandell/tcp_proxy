# TCP Proxy

## Overview

TCP Proxy is a lightweight and efficient proxy server designed to forward TCP connections between a source and a destination. The application reads configuration settings from an INI file and utilizes Boost.Asio for asynchronous networking and spdlog for logging.

## Features

- Asynchronous TCP proxying using Boost.Asio
- Configurable source and destination addresses via INI file
- Threaded handling of client connections
- Robust error handling and logging using spdlog

## Requirements

- C++17 or later
- Boost.Asio
- spdlog
- INI parser library
- CMake (minimum version 3.10)

## Installation

### Linux

```sh
sudo apt-get install libboost-all-dev
sudo apt-get install cmake
mkdir build && cd build
cmake ..
make
```

### Windows

1. Install Boost and spdlog
2. Set the `BOOST_ROOT` variable in `CMakeLists.txt`
3. Build with CMake

```sh
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## Configuration

Create a `config.ini` file in the root directory with the following structure:

```ini
[source]
ip = 127.0.0.1
port = 8080

[destination]
ip = 192.168.1.100
port = 9090
```

## Usage

Run the compiled executable:

```sh
./tcp_proxy
```

The proxy will listen on the source IP and port, forwarding traffic to the destination.

## Code Structure

- `main.cpp` - Entry point of the application.
- `TcpProxy.cpp` - Handles TCP proxying and connection forwarding.
- `Logger.cpp` - Provides logging functionality.
- `Config.cpp` - Parses and loads configuration settings.

## License

This project is licensed under the MIT License.
