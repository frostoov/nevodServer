#ifndef RPCSERVER_H
#define RPCSERVER_H

#include <cstdint>
#include <memory>
#include <include/xsonrpc/server.h>
#include <include/xsonrpc/dispatcher.h>
#include <include/xsonrpc/jsonformathandler.h>

#include "easrpc.hpp"
#include "uranrpc.hpp"
#include "../eas/easstation.hpp"

class RpcServer	: public xsonrpc::Server {
public:
	using EasRpcPtr		= std::unique_ptr<EasRpc>;
	using UranRpcPtr	= std::unique_ptr<UranRpc>;
	using EasStationPtr	= std::unique_ptr<EasStation>;

	explicit RpcServer(uint16_t	port);
	~RpcServer();

	void	run();

protected:
	void	initializeDispatcherOfEasRpc();

private:
	xsonrpc::Dispatcher	dispatcher_;

	EasRpcPtr		easRpc_;
	UranRpcPtr		uranRpc_;
	EasStationPtr	easStation_;
};

#endif//RPCSERVER_H
