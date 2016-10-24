#include "tcpdataconnection.hpp"

#include <iostream>  // TODO

TcpDataConnection::TcpDataConnection(boost::asio::io_service& service)
    : socket_(service), isConnected_(false) {}

TcpDataConnection::~TcpDataConnection() {}

TcpDataConnection::TcpDataConnectionPtr TcpDataConnection::create(
    boost::asio::io_service& service) {
    return std::make_shared<TcpDataConnection>(service);
}

boost::asio::ip::tcp::socket& TcpDataConnection::getSocket() {
    return socket_;
}

void TcpDataConnection::start() {
    std::cout << "I am here. I am Data Connection" << std::endl;
    isConnected_ = true;
}

bool TcpDataConnection::isConnected() const {
    return isConnected_;
}

bool TcpDataConnection::sendData(const std::vector<uint8_t>& data) {
    boost::asio::async_write(
        socket_, boost::asio::buffer(data),
        boost::bind(&TcpDataConnection::handleWrite, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    return true;
}

void TcpDataConnection::handleWrite(const boost::system::error_code& error,
                                    size_t) {
    if (!error) {
        std::cout << "Data has been sent to client!!\t" << error.message()
                  << std::endl;
    }
}
