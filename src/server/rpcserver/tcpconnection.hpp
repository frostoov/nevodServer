#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "jsonformathandler.hpp"
#include "dispatcher.hpp"
#include "jsonwriter.hpp"
#include "jsonreader.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
	using TcpConnectionPtr	= std::shared_ptr<TcpConnection>;
	using FormatHandlerPtr	= std::shared_ptr<JsonFormatHandler>;
	using DispatcherPtr			= std::shared_ptr<Dispatcher>;

	TcpConnection(boost::asio::io_service& service, Dispatcher& dispatcher, std::vector<JsonFormatHandler*>&	formatHandlersIn);
	~TcpConnection();

	static TcpConnectionPtr create(boost::asio::io_service&	service, Dispatcher& dispatcher, std::vector<JsonFormatHandler *> &formatHandlers);
	boost::asio::ip::tcp::socket&	getSocket();
	void	start();

protected:
	void	handleWrite(const boost::system::error_code& error, size_t);
	void	handleRead(const boost::system::error_code& error);

private:
	Dispatcher& myDispatcher;
	std::vector<JsonFormatHandler*> myFormatHandlers;
	std::shared_ptr<JsonFormatHandler>	formatHandler;
	std::unique_ptr<JsonWriter>	writer;

	boost::asio::ip::tcp::socket	socket;
	std::string message;
	std::vector<char>	buf;
	boost::asio::streambuf	response_;
};

#endif	//TCPCONNECTION_H
