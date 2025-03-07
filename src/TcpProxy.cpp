
#include "include/TcpProxy.h"
#include "include/Logger.h"
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <memory>

TcpProxy::TcpProxy(const std::string &source_ip, uint16_t source_port,
                   const std::string &dest_ip, uint16_t dest_port)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(source_ip), source_port)),
      destination_ip_(dest_ip), destination_port_(dest_port), running_(false) {}

void TcpProxy::start()
{
    try
    {
        running_ = true;
        accept_connections();
        io_context_.run();
    }
    catch (const std::exception &e)
    {
        Logger::get_logger()->error("Error starting TcpProxy: {}", e.what());
        stop();
    }
}

void TcpProxy::stop()
{
    running_ = false;
    io_context_.stop();
}

void TcpProxy::accept_connections()
{
    auto client_socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*client_socket, [this, client_socket](boost::system::error_code ec)
                           {
        if (!ec) {
            Logger::get_logger()->info("Accepted new connection from {}", client_socket->remote_endpoint().address().to_string());
            handle_client_connection(client_socket);
        } else {
            Logger::get_logger()->error("Error accepting connection: {}", ec.message());
        }
        if (running_) {
            accept_connections();
        } });
}

void TcpProxy::handle_client_connection(std::shared_ptr<boost::asio::ip::tcp::socket> client_socket)
{
    std::thread([this, client_socket]()
                {
        try {
            boost::asio::ip::tcp::socket server_socket(io_context_);
            boost::asio::ip::tcp::endpoint server_endpoint(boost::asio::ip::make_address(destination_ip_), destination_port_);
            server_socket.connect(server_endpoint);
            forward_data(client_socket, std::make_shared<boost::asio::ip::tcp::socket>(std::move(server_socket)));
        } catch (const std::exception& e) {
            Logger::get_logger()->error("Error handling client connection: {}", e.what());
        } })
        .detach();
}

void TcpProxy::forward_data(std::shared_ptr<boost::asio::ip::tcp::socket> client_socket,
                            std::shared_ptr<boost::asio::ip::tcp::socket> server_socket)
{
    try
    {
        std::array<char, 1024> buffer;
        while (running_)
        {
            boost::system::error_code ec;
            size_t bytes_received = client_socket->read_some(boost::asio::buffer(buffer), ec);
            if (ec)
                break;
            boost::asio::write(*server_socket, boost::asio::buffer(buffer, bytes_received));

            bytes_received = server_socket->read_some(boost::asio::buffer(buffer), ec);
            if (ec)
                break;
            boost::asio::write(*client_socket, boost::asio::buffer(buffer, bytes_received));
        }
    }
    catch (const std::exception &e)
    {
        Logger::get_logger()->error("Error during data forwarding: {}", e.what());
    }
}
