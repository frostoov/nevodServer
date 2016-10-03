#ifndef RPCSERVER_HPP
#define RPCSERVER_HPP

#include <string>
#include <boost/asio.hpp>

#include "dispatcher.hpp"
#include "tcpcontrolconnection.hpp"
#include "tcpdataconnection.hpp"

class RpcServer {
public:
    using ioServicePtr = std::shared_ptr<boost::asio::io_service>;
    using TcpControlConnectionPtr = std::shared_ptr<TcpControlConnection>;
    using TcpDataConnectionPtr = std::shared_ptr<TcpDataConnection>;

    struct Connections {
        Connections(boost::asio::io_service& service, Dispatcher& dispatcher) {
            control = TcpControlConnection::create(service, dispatcher);
            data = TcpDataConnection::create(service);
        }

        TcpControlConnectionPtr control;
        TcpDataConnectionPtr data;
    };

    RpcServer(uint16_t controlPort, uint16_t dataPort);
    ~RpcServer();

    RpcServer(const RpcServer&) = delete;
    RpcServer& operator=(const RpcServer&) = delete;
    RpcServer(RpcServer&&) = delete;
    RpcServer& operator=(RpcServer&&) = delete;

    void run();

    Dispatcher& getDispatcher();
    ioServicePtr& getIoService();

protected:
    void startControlAccept();
    void startDataAccept();
    void addClientToClients();
    void handleControlAccept(TcpControlConnectionPtr newConnection,
                      const boost::system::error_code& error);
    void handleDataAccept(TcpDataConnectionPtr newConnection,
                      const boost::system::error_code& error);
    void handleRequest(const boost::system::error_code& error, size_t);

private:
    Dispatcher dispatcher_;

    ioServicePtr service_;
    boost::asio::ip::tcp::acceptor controlAcceptor_;
    boost::asio::ip::tcp::acceptor dataAcceptor_;
    std::vector<Connections> clients_;
};

#endif//RPCSERVER_HPP
