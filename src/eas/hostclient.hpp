#ifndef HOSTCLIENT_HPP
#define HOSTCLIENT_HPP

#include <thread>
#include <memory>
#include <cstdint>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "../observer/observer.hpp"
#include "client.hpp"

class HostClient : public Client,
				   public std::enable_shared_from_this<HostClient> {
public:
	using IoServicePtr = std::shared_ptr<boost::asio::io_service>;
	using HostClientPtr = std::shared_ptr<HostClient>;

	HostClient(const std::string& ip,
						uint16_t port,
						const IoServicePtr& service);
	~HostClient();

	bool connectToHost();
	bool disconnectFromHost();
	void readRegister(uint32_t address);
	void writeRegister3000(uint32_t address, uint32_t data);
	void writeRegister3002(uint32_t address, uint32_t data);
	bool isStopped() const;
	void clearData();

	const std::vector<uint8_t>& getData() const;
	Message getMessage() const;

	void write(int32_t number, bool isBan) {}

protected:
	void startConnect();
	void startRead();
	void startWrite(const std::vector<char>& message);
	void connectHandler(const boost::system::error_code& error);
	void readHandler(const boost::system::error_code& error, size_t);
	void writeHandler(const boost::system::error_code& error, size_t);
	void checkDeadline();

private:
	boost::asio::ip::tcp::socket socket_;
	boost::asio::streambuf inputBuffer_;
	boost::asio::deadline_timer deadlineTimer_;
	boost::asio::deadline_timer heartbeatTimer_;
	std::string ip_;
	uint16_t port_;
	bool stopped_;
	std::vector<uint8_t> data_;
	Message message_;
};

class HostClientFactory : public ClientFactory {
public:
	using IoServicePtr = std::shared_ptr<boost::asio::io_service>;
	using ClientPtr = std::shared_ptr<HostClient>;

	static ClientPtr create(const std::string& ip,
							uint16_t port,
							const IoServicePtr& service) {
		return std::make_shared<HostClient>(ip, port, service);
	}
};

#endif  // HOSTCLIENT_HPP
