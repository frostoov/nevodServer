#ifndef SERVER_H
#define SERVER_H

#include "dispatcher.hpp"
#include "tcpconnection.hpp"

#include <string>
#include <boost/asio.hpp>

class Server
{
public:
	using ioServicePtr = std::shared_ptr<boost::asio::io_service>;

	Server(unsigned short port);
	~Server();

	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;
	Server(Server&&) = delete;
	Server& operator=(Server&&) = delete;

	void RegisterFormatHandler(JsonFormatHandler& formatHandler);

	void Run();
	int GetFileDescriptor();
	void OnReadableFileDescriptor();

	Dispatcher& GetDispatcher() { return myDispatcher; }
	ioServicePtr& GetIoService()   {return service;}

protected:
	void  startAccept();
	void  handleAccept(TcpConnection::TcpConnectionPtr newConnection, const boost::system::error_code& error);
	void  handleRequest(const boost::system::error_code& error, size_t);

private:  
	Dispatcher myDispatcher;
	std::vector<JsonFormatHandler*> myFormatHandlers;

	ioServicePtr service;
	boost::asio::ip::tcp::acceptor acceptor;
};

#endif
