#include "server.hpp"

#include "jsonwriter.hpp"

#include <vector>

#include <iostream>	//TODO

Server::Server(unsigned short port)
	:	service_(std::make_shared<boost::asio::io_service>()),
	  acceptor_(*(service_.get()), boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))	{

}

Server::~Server()	{

}

void Server::run()	{
	startAccept();
	service_->run();
}

void Server::startAccept()	{
	TcpConnection::TcpConnectionPtr newConnection =
			TcpConnection::create(acceptor_.get_io_service(), dispatcher_);

	acceptor_.async_accept(newConnection->getSocket(),
						  boost::bind(&Server::handleAccept,
									  this, newConnection,
									  boost::asio::placeholders::error));
}

void Server::handleAccept(TcpConnection::TcpConnectionPtr newConnection, const boost::system::error_code& error)	{
	if (!error)	{
		static int numberOfClient = 0;
		std::cout << "His number is " << numberOfClient << std::endl;
		numberOfClient++;
		newConnection->start();
	}
	startAccept();
}

void Server::handleRequest(const boost::system::error_code &error, size_t)	{

}
