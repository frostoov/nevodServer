#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdint>
#include <memory>

#include "rpcserver/rpcserver.hpp"
#include "../eas/easstation.hpp"

class Server : public RpcServer, public Observer {
public:
    using EasStationPtr = std::unique_ptr<EasStation>;
    using IoServicePtr = std::shared_ptr<boost::asio::io_service>;

    Server(uint16_t controlPort, uint16_t dataPort);
    ~Server();

    void update(const Subject* subject);

    void start();

protected:
    void initializeDispatcherOfEasRpc();

private:
    Dispatcher dispatcher_;

    EasStationPtr easStation_;
};

#endif//SERVER_HPP
