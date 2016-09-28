#ifndef RPCSERVERTEST_HPP
#define RPCSERVERTEST_HPP

#include <memory>

#include "../../src/server/server.hpp"
#include "tcpconnectiontest.hpp"

class RpcServerTest : public RpcServer {
public:
	using TcpConnectionTestPtr = std::shared_ptr<TcpConnectionTest>;

	RpcServerTest(uint16_t port) : RpcServer(port) {
		connection_ = std::make_shared<TcpConnectionTest>(
			*(getIoService().get()), getDispatcher());

		auto& dispatcher = getDispatcher();

		dispatcher.addMethod("plusTwoNumbers", &RpcServerTest::plusTwoNumbers,
							 *this);
		dispatcher.addMethod("concatTwoStrings",
							 &RpcServerTest::concatTwoStrings, *this);
	}

	~RpcServerTest() {}

	int32_t plusTwoNumbers(int32_t first, int32_t second) {
		return first + second;
	}

	std::string concatTwoStrings(const std::string& first,
								 const std::string& second) {
		return first + second;
	}

	TcpConnectionTestPtr getTcpConnectionTest() { return connection_; }

private:
	TcpConnectionTestPtr connection_;
};

#endif//RPCSERVERTEST_HPP
