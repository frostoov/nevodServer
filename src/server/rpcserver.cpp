#include "rpcserver.hpp"

RpcServer::RpcServer(uint16_t port) : Server(port) {
    easRpc_ = std::make_unique<EasRpc>(this->getIoService());
    uranRpc_ = std::make_unique<UranRpc>(dispatcher_);

    initializeDispatcherOfEasRpc();
}

RpcServer::~RpcServer() {}

void RpcServer::start() {
    this->run();
}

void RpcServer::initializeDispatcherOfEasRpc() {
    auto& dispatcher = getDispatcher();

    //	bool run = true;
    //	dispatcher_.AddMethod("exit", [&] () { run = false; }).SetHidden();

    dispatcher.addMethod("eas_writeBanOfTimestamps",
                         &EasRpc::eas_writeBanOfTimestamps, *(easRpc_.get()));
    dispatcher.addMethod("eas_writeRegisterOfMasks",
                         &EasRpc::eas_writeRegisterOfMasks, *(easRpc_.get()));
    dispatcher.addMethod("eas_writeHardReset", &EasRpc::eas_writeHardReset,
                         *(easRpc_.get()));
    dispatcher.addMethod("eas_writePermissionOfMasters",
                         &EasRpc::eas_writePermissionOfMasters,
                         *(easRpc_.get()));
    dispatcher.addMethod("eas_writeControlDma", &EasRpc::eas_writeControlDma,
                         *(easRpc_.get()));
    dispatcher.addMethod("eas_writeStartTaskMaster",
                         &EasRpc::eas_writeStartTaskMaster, *(easRpc_.get()));
    dispatcher.addMethod("eas_writeRegisterOfReadData",
                         &EasRpc::eas_writeRegisterOfReadData,
                         *(easRpc_.get()));
}
