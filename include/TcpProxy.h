
#ifndef TCP_PROXY_H
#define TCP_PROXY_H

#include <boost/asio.hpp>
#include <memory>
#include <string>

class TcpProxy
{
public:
    TcpProxy(const std::string &source_ip, uint16_t source_port,
             const std::string &dest_ip, uint16_t dest_port);
    void start();
    void stop();

private:
    void accept_connections();
    void handle_client_connection(std::shared_ptr<boost::asio::ip::tcp::socket> client_socket);
    void forward_data(std::shared_ptr<boost::asio::ip::tcp::socket> client_socket,
                      std::shared_ptr<boost::asio::ip::tcp::socket> server_socket);

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::string destination_ip_;
    uint16_t destination_port_;
    bool running_;
};

#endif // TCP_PROXY_H
