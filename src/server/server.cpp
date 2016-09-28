#include "server.hpp"

Server::Server(uint16_t port) : RpcServer(port) {
    easStation_ = std::make_unique<EasStation>(this->getIoService());

    initializeDispatcherOfEasRpc();
}

Server::~Server() {}

void Server::start() {
    this->run();
}

void Server::initializeDispatcherOfEasRpc() {
    auto& dispatcher = getDispatcher();

    //	bool run = true;
    //	dispatcher_.AddMethod("exit", [&] () { run = false; }).SetHidden();

    dispatcher.addMethod("eas_writeBanOfTimestamps",
                         &EasStation::writeBanOfTimestamps,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeRegisterOfMasks",
                         &EasStation::writeRegisterOfMasks,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeHardReset", &EasStation::writeHardReset,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writePermissionOfMasters",
                         &EasStation::writePermissionOfMasters,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeControlDma",
                         &EasStation::writeControlDma,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeStartTaskMaster",
                         &EasStation::writeStartTaskMaster,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeRegisterOfReadData",
                         &EasStation::writeRegisterOfReadData,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeRegisterOfReadData",
                         &EasStation::writeRegisterOfReadData,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writePermissionOfData",
                         &EasStation::writePermissionOfData,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeClearDataBuffer",
                         &EasStation::writeClearDataBuffer,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeResetRegister",
                         &EasStation::writeResetRegister,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writePermissionOfTimer",
                         &EasStation::writePermissionOfTimer,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeSetCoincidence",
                         &EasStation::writeSetCoincidence,
                         *(easStation_.get()));
}
