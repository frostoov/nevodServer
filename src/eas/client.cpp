#include "client.hpp"

#include <iostream>	//TODO

Client::Client(const std::string& ip, uint16_t port, const IoServicePtr &service)
	:	socket_(*(service.get())), ip_(ip), port_(port), stopped_(true),
		deadlineTimer_(*(service.get())), heartbeatTimer_(*(service.get()))	{

}

Client::~Client()	{

}

void Client::start()	{
	stopped_ = false;
	startConnect();

	deadlineTimer_.async_wait(boost::bind(&Client::checkDeadline,
										  shared_from_this()));
}

bool Client::connectToHost() {
//	boost::asio::ip::tcp::endpoint	ep(boost::asio::ip::address::from_string(ip_), port_);

//	socket_.async_connect(ep, boost::bind(&Client::connectHandler,
//								shared_from_this(),
//								boost::asio::placeholders::error));
}

bool Client::disconnectFromHost() {
	stopped_ = true;
	socket_.close();
	deadlineTimer_.cancel();
	heartbeatTimer_.cancel();
	return true;
}

bool Client::isStopped()	const {
	return stopped_;
}

void Client::startConnect()	{
	deadlineTimer_.expires_from_now(boost::posix_time::seconds(60));
	boost::asio::ip::tcp::endpoint	ep(boost::asio::ip::address::from_string(ip_), port_);
	socket_.async_connect(ep, boost::bind(&Client::connectHandler,
										  shared_from_this(),
										  boost::asio::placeholders::error));
}

void Client::startRead()	{
//	deadlineTimer_.expires_from_now(boost::posix_time::seconds(30));

	boost::asio::async_read_until(socket_, inputBuffer_, '\n',
								  boost::bind(&Client::readHandler,
											  shared_from_this(),
											  boost::asio::placeholders::error,
											  boost::asio::placeholders::bytes_transferred));
}

void Client::startWrite()	{
	if (stopped_)
		return;

	boost::asio::async_write(socket_, boost::asio::buffer("\n"),
							 boost::bind(&Client::writeHandler,
										 shared_from_this(),
										 boost::asio::placeholders::error,
										 boost::asio::placeholders::bytes_transferred));
}

void Client::connectHandler(const boost::system::error_code& error)	{
	if (stopped_)
		return;
	if (!error)	{
		startRead();
		startWrite();
	}
}

void Client::readHandler(const boost::system::error_code &error, size_t)	{
	if (stopped_)
		return;

	std::cout << "Reading:\t" << error.message() << std::endl;

	if (!error)	{
		std::string line;
		std::istream is(&inputBuffer_);
		std::getline(is, line);

		if (!line.empty())
			std::cout << "Received: " << line << std::endl;

		startRead();
	}
	else {
		std::cout << "Error reading" << std::endl;
		disconnectFromHost();
	}
}

void Client::writeHandler(const boost::system::error_code &error, size_t)	{
	if (stopped_)
		return;

	std::cout << "Writing:\t" << error.message() << std::endl;

	if (!error)	{
		heartbeatTimer_.expires_from_now(boost::posix_time::seconds(10));
		heartbeatTimer_.async_wait(boost::bind(&Client::startWrite, shared_from_this()));
	}
	else {
		std::cout << "Error writing" << std::endl;
		disconnectFromHost();
	}
}

void Client::checkDeadline()	{
	if (stopped_)
		return;
	std::cout << "Deadline" << std::endl;
	if (deadlineTimer_.expires_at() <= boost::asio::deadline_timer::traits_type::now())	{
		socket_.close();
		deadlineTimer_.expires_at(boost::posix_time::pos_infin);
	}
	deadlineTimer_.async_wait(boost::bind(&Client::checkDeadline,
										  shared_from_this()));
}
