#ifndef RPCSERVER_H
#define RPCSERVER_H

#include <cstdint>
#include <memory>

#include "server.hpp"
#include "easrpc.hpp"
#include "uranrpc.hpp"

class RpcServer	: public  xsonrpc::Server	{
public:
	using EasRpcPtr		= std::unique_ptr<EasRpc>;
	using UranRpcPtr	= std::unique_ptr<UranRpc>;

	explicit RpcServer(uint16_t	port);
	~RpcServer();

	void	run();

protected:
	void	initializeDispatcherOfEasRpc();

private:
	xsonrpc::Dispatcher	dispatcher_;

	EasRpcPtr		easRpc_;
	UranRpcPtr		uranRpc_;
};

#endif//RPCSERVER_H
