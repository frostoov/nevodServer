#include <vector>
#include <iostream>  //TODO

#include "rpcserver.hpp"
#include "jsonwriter.hpp"

RpcServer::RpcServer(uint16_t controlPort, uint16_t dataPort)
    : service_(std::make_shared<boost::asio::io_service>()),
      controlAcceptor_(
          *(service_.get()),
          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                         controlPort)),
      dataAcceptor_(*(service_.get()),
                    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                   dataPort)) {}

RpcServer::~RpcServer() {}

void RpcServer::run() {
    addClientToClients();
    startControlAccept();
    startDataAccept();
    service_->run();
}

Dispatcher& RpcServer::getDispatcher() {
    return dispatcher_;
}

RpcServer::ioServicePtr& RpcServer::getIoService() {
    return service_;
}

void RpcServer::startControlAccept() {
    controlAcceptor_.async_accept(
        clients_.back().control->getSocket(),
        boost::bind(&RpcServer::handleControlAccept, this,
                    clients_.back().control, boost::asio::placeholders::error));
}

void RpcServer::startDataAccept() {
    dataAcceptor_.async_accept(
        clients_.back().data->getSocket(),
        boost::bind(&RpcServer::handleDataAccept, this, clients_.back().data,
                    boost::asio::placeholders::error));
}

void RpcServer::addClientToClients() {
    if (clients_.empty()) {
        clients_.push_back(Connections(*(service_.get()), dispatcher_));
        return;
    }
    if (clients_.back().control->isConnected() &&
        clients_.back().data->isConnected())
        clients_.push_back(Connections(*(service_.get()), dispatcher_));
}

void RpcServer::handleControlAccept(TcpControlConnectionPtr newConnection,
                                    const boost::system::error_code& error) {
    if (!error) {
        static int numberOfClient = 0;
        std::cout << "His control number is " << numberOfClient << std::endl;
        numberOfClient++;
        newConnection->start();
    }
    addClientToClients();
    startControlAccept();
}

void RpcServer::handleDataAccept(RpcServer::TcpDataConnectionPtr newConnection,
                                 const boost::system::error_code& error) {
    if (!error) {
        static int numberOfClient = 0;
        std::cout << "His data number is " << numberOfClient << std::endl;
        numberOfClient++;
        newConnection->start();
    }
    addClientToClients();
    startDataAccept();
}

void RpcServer::handleRequest(const boost::system::error_code& error, size_t) {}
