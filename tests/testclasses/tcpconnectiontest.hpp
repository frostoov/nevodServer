#ifndef TCPCONNECTIONTEST_HPP
#define TCPCONNECTIONTEST_HPP

#include "../../src/server/rpcserver/tcpconnection.hpp"

class TcpConnectionTest : public TcpConnection {
public:
	TcpConnectionTest(boost::asio::io_service& service, Dispatcher& dispatcher)
		: TcpConnection(service, dispatcher) {}

	std::string answerToRequestTest(const std::string& message) {
		return answerToRequest(message);
	}
};

#endif  // TCPCONNECTIONTEST_HPP
