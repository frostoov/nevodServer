#include "server.hpp"

#include "formathandler.hpp"
#include "reader.hpp"
#include "writer.hpp"

#include <vector>

#include <iostream>	//TODO

namespace {

const size_t MAX_REQUEST_SIZE = 16 * 1024;

struct HttpError
{
  unsigned int StatusCode;
};

struct ConnectionInfo
{
  std::string Buffer;
  xsonrpc::FormatHandler* FormatHandler;
  std::unique_ptr<xsonrpc::Writer> Writer;
};

} // namespace

namespace xsonrpc {

Server::Server(unsigned short port)
	:	service(std::make_shared<boost::asio::io_service>()),
	  acceptor(*(service.get()), boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{

}

Server::~Server()
{

}

void Server::RegisterFormatHandler(FormatHandler& formatHandler)
{
	myFormatHandlers.push_back(&formatHandler);
}

void Server::Run()
{
	startAccept();
	service->run();
}

int Server::GetFileDescriptor()
{

}

void Server::OnReadableFileDescriptor()
{

}

void Server::startAccept()
{
	TcpConnection::TcpConnectionPtr newConnection =
			TcpConnection::create(acceptor.get_io_service(), myDispatcher, myFormatHandlers);

	acceptor.async_accept(newConnection->getSocket(),
							 boost::bind(&Server::handleAccept,
										 this, newConnection,
										 boost::asio::placeholders::error));
}

void Server::handleAccept(TcpConnection::TcpConnectionPtr newConnection, const boost::system::error_code& error)
{
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

} // namespace xsonrpc
