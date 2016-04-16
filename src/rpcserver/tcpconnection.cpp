#include "tcpconnection.hpp"

#include <iostream>	//TODO

namespace xsonrpc {

TcpConnection::TcpConnection(boost::asio::io_service &service, Dispatcher &dispatcher, std::vector<FormatHandler *> &formatHandlersIn)
	:	socket(service), myDispatcher(dispatcher), myFormatHandlers(formatHandlersIn)
{
	formatHandler = std::make_shared<JsonFormatHandler>();
	buf.resize(2048);

	for (auto str : myDispatcher.GetMethodNames())
		std::cout << str << std::endl;
}

TcpConnection::~TcpConnection()
{

}

TcpConnection::TcpConnectionPtr	TcpConnection::create(boost::asio::io_service &service, Dispatcher &dispatcher, std::vector<FormatHandler*>& formatHandlers)
{
	return std::make_shared<TcpConnection>(service, dispatcher, formatHandlers);
}

boost::asio::ip::tcp::socket& TcpConnection::getSocket()
{
	return socket;
}

void	TcpConnection::start()
{
	std::cout << "I am in start!!" << std::endl;

//	async_write(socket, boost::asio::buffer(message),
//				boost::bind(&TcpConnection::handleWrite, shared_from_this(),
//							boost::asio::placeholders::error,
//							boost::asio::placeholders::bytes_transferred));

//	boost::asio::async_read(socket, boost::asio::buffer(buf),
//									boost::bind(&TcpConnection::handleRead, shared_from_this(),
//													boost::asio::placeholders::error,
//													boost::asio::placeholders::bytes_transferred));

	boost::asio::async_read_until(socket, response_, ";",
									boost::bind(&TcpConnection::handleRead, shared_from_this(),
													boost::asio::placeholders::error
													));

}

void	TcpConnection::handleWrite(const boost::system::error_code &error, size_t)
{
	std::cout << "I have wrriten that!!" << std::endl;
//	boost::asio::async_read_until(socket, response_, ";",
//									boost::bind(&TcpConnection::handleRead, shared_from_this(),
//													boost::asio::placeholders::error
//													));
}

void	TcpConnection::handleRead(const boost::system::error_code &error)
{
	std::cout << error.message() << std::endl;
//	if (error != 0)	{
//		return;
//	}

//	std::cout << buf.size() << std::endl;
//	std::cout << std::string(buf.begin(), buf.end()) << std::endl;

	std::istream	respStream(&response_);
	std::string		msg(std::istreambuf_iterator<char>(respStream), {});
	msg.erase(msg.end() - 1);
	std::cout << msg << std::endl;

	writer = std::unique_ptr<Writer>(new JsonWriter());

	try {
		auto reader = std::unique_ptr<Reader>(new JsonReader(std::move(msg)));
		Request	request = reader->GetRequest();
		reader.reset();

		auto response = myDispatcher.Invoke(
					request.GetMethodName(), request.GetParameters(), request.GetId());
		response.Write(*writer.get());
	} catch (const Fault& ex)	{
		Response(ex.GetCode(), ex.GetString(), Value()).Write(*writer.get());
	}

	std::cout << std::string(writer->GetData()) << std::endl;

	boost::asio::async_write(socket, boost::asio::buffer(std::string(writer->GetData())),
													 boost::bind(&TcpConnection::handleWrite, shared_from_this(),
																			 boost::asio::placeholders::error,
																			 boost::asio::placeholders::bytes_transferred));

}

}	//namespace xsonrpc
