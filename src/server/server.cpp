#include "server.hpp"

Server::Server(uint16_t controlPort, uint16_t dataPort)
    : RpcServer(controlPort, dataPort) {
    easStation_ = std::make_unique<EasStation>(this->getIoService());
    easStation_->attach(this);

    initializeDispatcherOfEasRpc();
}

Server::~Server() {
//    easStation_->detach(this);
}

void Server::update(const Subject* subject) {
    if (subject == easStation_.get()) {
        for (auto& client : clients_)
            client.data->sendData(easStation_->getData());
    }
}

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
    dispatcher.addMethod("eas_writeControlDma", &EasStation::writeControlDma,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeStartTaskMaster",
                         &EasStation::writeStartTaskMaster,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeRegisterOfReadData",
                         &EasStation::writeRegisterOfReadData,
                         *(easStation_.get()));
    //    dispatcher.addMethod("eas_writeRegisterOfReadData",
    //                         &EasStation::writeRegisterOfReadData,
    //                         *(easStation_.get()));
    dispatcher.addMethod("eas_writePermissionOfData",
                         &EasStation::writePermissionOfData,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeClearDataBuffer",
                         &EasStation::writeClearDataBuffer,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeResetRegister",
                         &EasStation::writeResetRegister, *(easStation_.get()));
    dispatcher.addMethod("eas_writePermissionOfTimer",
                         &EasStation::writePermissionOfTimer,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeSetCoincidence",
                         &EasStation::writeSetCoincidence,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeResetCounter",
                         &EasStation::writeResetCounter, *(easStation_.get()));
    dispatcher.addMethod("eas_writeSetTimeGate", &EasStation::writeSetTimeGate,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeActiveChannels",
                         &EasStation::writeActiveChannels,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeControlTrigger",
                         &EasStation::writeControlTrigger,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeProgramTrigger",
                         &EasStation::writeProgramTrigger,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeResetVme", &EasStation::writeResetVme,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeTime", &EasStation::writeTime,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeControlRegister",
                         &EasStation::writeControlRegister,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeThreshold", &EasStation::writeThreshold,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeDelay", &EasStation::writeDelay,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_writeResetChannel",
                         &EasStation::writeResetChannel, *(easStation_.get()));
    dispatcher.addMethod("eas_writeSmoothing", &EasStation::writeSmoothing,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_connectToHost", &EasStation::connectToHost,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_addMasterToHost", &EasStation::addMasterToHost,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_addAdcToMaster", &EasStation::addAdcToMaster,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_setTaskTable", &EasStation::setTaskTable,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_write200200", &EasStation::write200200,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_resolutionDataZero",
                         &EasStation::resolutionDataZero, *(easStation_.get()));
    dispatcher.addMethod("eas_resolutionAndForbidOfData",
                         &EasStation::resolutionAndForbidOfData,
                         *(easStation_.get()));
    dispatcher.addMethod("eas_runQueue",
                         &EasStation::runQueue, *(easStation_.get()));
}
