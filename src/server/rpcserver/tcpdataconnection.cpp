#include "tcpdataconnection.hpp"

#include <iostream> // TODO

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
