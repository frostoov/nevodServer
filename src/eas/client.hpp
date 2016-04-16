#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <memory>
#include <cstdint>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "../observer/observer.hpp"

class Client : public Subject	{
public:
	using	IoServicePtr	= std::shared_ptr<boost::asio::io_service>;

	explicit Client(const std::string& ip, uint16_t port, const IoServicePtr& service);
	~Client();

	void	run();

protected:
	void	connectHandler(const boost::system::error_code& error);
	void	readHandler(const boost::system::error_code& error, size_t);
	void	writeHandler(const boost::system::error_code& error, size_t);

private:
	boost::asio::ip::tcp::socket	socket_;
	std::string	ip_;
	uint16_t	port_;
};

#endif // CLIENT_H
