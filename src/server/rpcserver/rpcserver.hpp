#ifndef RPCSERVER_HPP
#define RPCSERVER_HPP

#include <string>
#include <boost/asio.hpp>

#include "dispatcher.hpp"
#include "tcpconnection.hpp"

class RpcServer {
public:
    using ioServicePtr = std::shared_ptr<boost::asio::io_service>;

	RpcServer(unsigned short port);
	~RpcServer();

	RpcServer(const RpcServer&) = delete;
	RpcServer& operator=(const RpcServer&) = delete;
	RpcServer(RpcServer&&) = delete;
	RpcServer& operator=(RpcServer&&) = delete;

    void run();

    Dispatcher& getDispatcher();
    ioServicePtr& getIoService();

protected:
    void startAccept();
    void handleAccept(TcpConnection::TcpConnectionPtr newConnection,
                      const boost::system::error_code& error);
    void handleRequest(const boost::system::error_code& error, size_t);

private:
    Dispatcher dispatcher_;

    ioServicePtr service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

#endif//RPCSERVER_HPP
