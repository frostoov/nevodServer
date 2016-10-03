#ifndef TCPCONNECTIONTEST_HPP
#define TCPCONNECTIONTEST_HPP

#include "../../src/server/rpcserver/tcpcontrolconnection.hpp"

class TcpConnectionTest : public TcpControlConnection {
public:
	TcpConnectionTest(boost::asio::io_service& service, Dispatcher& dispatcher)
        : TcpControlConnection(service, dispatcher) {}

	std::string answerToRequestTest(const std::string& message) {
		return answerToRequest(message);
	}
};

#endif  // TCPCONNECTIONTEST_HPP
