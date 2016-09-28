#include <vector>
#include <iostream>  //TODO

#include "rpcserver.hpp"
#include "jsonwriter.hpp"

RpcServer::RpcServer(unsigned short port)
    : service_(std::make_shared<boost::asio::io_service>()),
      acceptor_(
          *(service_.get()),
          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

RpcServer::~RpcServer() {}

void RpcServer::run() {
    startAccept();
    service_->run();
}

Dispatcher&RpcServer::getDispatcher() {
    return dispatcher_;
}

RpcServer::ioServicePtr&RpcServer::getIoService() {
    return service_;
}

void RpcServer::startAccept() {
    TcpConnection::TcpConnectionPtr newConnection =
        TcpConnection::create(acceptor_.get_io_service(), dispatcher_);

    acceptor_.async_accept(
        newConnection->getSocket(),
        boost::bind(&RpcServer::handleAccept, this, newConnection,
                    boost::asio::placeholders::error));
}

void RpcServer::handleAccept(TcpConnection::TcpConnectionPtr newConnection,
                          const boost::system::error_code& error) {
    if (!error) {
        static int numberOfClient = 0;
        std::cout << "His number is " << numberOfClient << std::endl;
        numberOfClient++;
        newConnection->start();
    }
    startAccept();
}

void RpcServer::handleRequest(const boost::system::error_code& error, size_t) {}
