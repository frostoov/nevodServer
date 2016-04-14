#ifndef RPCSERVER_H
#define RPCSERVER_H

#include <cstdint>
#include <include/xsonrpc/server.h>

class RpcServer	: public xsonrpc::Server {
public:
	explicit RpcServer(uint16_t	port);
	~RpcServer();

protected:

private:

};

#endif//RPCSERVER_H
