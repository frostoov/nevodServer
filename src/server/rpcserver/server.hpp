#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <boost/asio.hpp>

#include "dispatcher.hpp"
#include "tcpconnection.hpp"

class Server	{
public:
	using ioServicePtr = std::shared_ptr<boost::asio::io_service>;

	Server(unsigned short port);
	~Server();

	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;
	Server(Server&&) = delete;
	Server& operator=(Server&&) = delete;

	void run();

	Dispatcher& getDispatcher() { return dispatcher_; }
	ioServicePtr& getIoService()   {return service_;}

protected:
	void  startAccept();
	void  handleAccept(TcpConnection::TcpConnectionPtr newConnection, const boost::system::error_code& error);
	void  handleRequest(const boost::system::error_code& error, size_t);

private:  
	Dispatcher dispatcher_;

	ioServicePtr service_;
	boost::asio::ip::tcp::acceptor acceptor_;
};

#endif
