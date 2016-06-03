#ifndef RPCSERVER_H
#define RPCSERVER_H

#include <cstdint>
#include <memory>

#include "rpcserver/server.hpp"
#include "easrpc.hpp"
#include "uranrpc.hpp"

class RpcServer : public Server {
public:
    using EasRpcPtr = std::unique_ptr<EasRpc>;
    using UranRpcPtr = std::unique_ptr<UranRpc>;

    explicit RpcServer(uint16_t port);
    ~RpcServer();

    void start();

protected:
    void initializeDispatcherOfEasRpc();

private:
    Dispatcher dispatcher_;

    EasRpcPtr easRpc_;
    UranRpcPtr uranRpc_;
};

#endif  // RPCSERVER_H
