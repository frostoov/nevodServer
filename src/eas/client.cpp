#include "client.hpp"

Client::Client(const std::string& ip, uint16_t port, const IoServicePtr &service)
	:	socket_(*(service.get())), ip_(ip), port_(port)	{

}

Client::~Client()	{

}

void	Client::run()	{
	boost::asio::ip::tcp::endpoint	ep(boost::asio::ip::address::from_string(ip_), port_);
	socket_.async_connect(ep, boost::bind(&Client::connectHandler,
								this,
								boost::asio::placeholders::error));
}

void	Client::connectHandler(const boost::system::error_code& error)	{

}

void	Client::readHandler(const boost::system::error_code &error, size_t)	{

}

void	Client::writeHandler(const boost::system::error_code &error, size_t)	{

}
