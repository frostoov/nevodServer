#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <memory>
#include <cstdint>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "../observer/observer.hpp"

class Client : public Subject, public std::enable_shared_from_this<Client>	{
public:
	using	IoServicePtr	= std::shared_ptr<boost::asio::io_service>;

	explicit Client(const std::string& ip, uint16_t port, const IoServicePtr& service);
	~Client();

	bool	connectToHost();
	bool	disconnectFromHost();
	void	start();
	bool	isStopped()	const;

protected:
	void	startConnect();
	void	startRead();
	void	startWrite();
	void	connectHandler(const boost::system::error_code& error);
	void	readHandler(const boost::system::error_code& error, size_t);
	void	writeHandler(const boost::system::error_code& error, size_t);
	void	checkDeadline();

private:
	boost::asio::ip::tcp::socket	socket_;
	boost::asio::streambuf			inputBuffer_;
	boost::asio::deadline_timer		deadlineTimer_;
	boost::asio::deadline_timer		heartbeatTimer_;
	std::string	ip_;
	uint16_t	port_;
	bool		stopped_;
	std::vector<char>	writeBuffer_;
};

#endif // CLIENT_H
