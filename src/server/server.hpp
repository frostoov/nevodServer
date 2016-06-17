#ifndef SERVER_H
#define SERVER_H

#include <cstdint>
#include <memory>

#include "rpcserver/rpcserver.hpp"
#include "easrpc.hpp"
#include "uranrpc.hpp"

class Server : public RpcServer {
public:
    using EasRpcPtr = std::unique_ptr<EasRpc>;
    using UranRpcPtr = std::unique_ptr<UranRpc>;

	Server(uint16_t port);
	~Server();

    void start();

protected:
    void initializeDispatcherOfEasRpc();

private:
    Dispatcher dispatcher_;

    EasRpcPtr easRpc_;
    UranRpcPtr uranRpc_;
};

#endif//SERVER_H
