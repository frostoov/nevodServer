#include "easstation.hpp"

EasStation::EasStation(const IoServicePtr& service) : service_(service) {
    //    auto host = addHost(0, "127.0.0.1", 2223, 2224);
    //    host->connectToHost();
}

EasStation::~EasStation() {}
//TODO say no to real factories
EasStation::HostPtr EasStation::addHost(uint32_t numberHost,
                                        const std::string& ip,
                                        uint16_t registerPort,
                                        uint16_t dataPort) {
    auto clientReg = RealClientFactory::create(ip, registerPort, service_);
    auto clientData = RealClientFactory::create(ip, dataPort, service_);
    auto clientQueue =
        RealQueueOfMessagesFactory::create(clientReg, clientData);
    HostPtr host = std::make_shared<Host>(clientQueue);
    hosts_.insert(std::pair<uint32_t, HostPtr>(numberHost, host));
    return host;
}

void EasStation::deleteHost(uint32_t numberHost) {
    hosts_.erase(numberHost);
}

bool EasStation::writeBanOfTimestamps(int idHost, bool isBan) {
    //	hosts_[0]->write(idHost, isBan);
    hosts_[0]->writeBanOfTimestamps(isBan);
    hosts_[0]->runQueue();
    return true;
}

bool EasStation::writeRegisterOfMasks(int idHost) {
    // TODO
}

bool EasStation::writeHardReset(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeHardReset();
    return true;
}

bool EasStation::writePermissionOfMasters(int idMaster, int isOpen) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
//    hosts_[idHost]->getMasters()[realIdMaster]->write
    return true;
}

bool EasStation::writeControlDma(int idHost, int isOn) {
    hosts_[idHost]->writeControlDma(static_cast<bool>(isOn));
    return true;
}

bool EasStation::writeStartTaskMaster(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    //    hosts_[idHost]->getMasters()[idMaster]-
    return true;
}

bool EasStation::writeRegisterOfReadData(int idHost,
                                         int isOnFirst,
                                         int isOnSecond,
                                         int isOnThird,
                                         int isOnFourth) {
    hosts_[idHost]->writeRegisterOfReadData(
        std::array<bool, 4>{{static_cast<bool>(isOnFirst),
                             static_cast<bool>(isOnSecond),
                             static_cast<bool>(isOnThird),
                             static_cast<bool>(isOnFourth)}});
    return true;
}

bool EasStation::writePermissionOfData(int idHost,
                                       int isOnFirst,
                                       int isOnSecond,
                                       int isOnThird,
                                       int isOnFourth) {
    hosts_[idHost]->writeResolutionOfLinks(
        std::array<bool, 4>{{static_cast<bool>(isOnFirst),
                             static_cast<bool>(isOnSecond),
                             static_cast<bool>(isOnThird),
                             static_cast<bool>(isOnFourth)}});
    return true;
}

bool EasStation::writeClearDataBuffer(int idHost) {
    hosts_[idHost]->writeClearDataBuffer(true);
    return true;
}

bool EasStation::writeResetRegister(int idMaster) {
    //    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    //    uint32_t realIdMaster = idMaster % 10;
    //    hosts_[idHost]->getMasters()[realIdMaster]->
}

bool EasStation::writePermissionOfTimer(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[idMaster]->writeResolutionOfTimer(true);
    return true;
}

bool EasStation::writeSetCoincidence(int idMaster, int coincidence) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[idMaster]->writeCoincidence(coincidence);
    return true;
}

bool EasStation::writeResetCounter(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeResetCounter();
    return true;
}

bool EasStation::writeSetTimeGate(int idMaster, int ns) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    uint16_t window = 0;  // TODO ns to window
    hosts_[idHost]->getMasters()[realIdMaster]->writeTemporaryWindow(window);
    return true;
}

bool EasStation::writeActiveChannels(int idMaster,
                                     int isOnFirst,
                                     int isOnSecond,
                                     int isOnThird,
                                     int isOnFourth,
                                     int isOnFifth,
                                     int isOnSixth,
                                     int isOnSeventh,
                                     int isOnEighth) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeMaskOfActiveChannels(
        std::array<bool, 8>{{static_cast<bool>(isOnFirst),
                             static_cast<bool>(isOnSecond),
                             static_cast<bool>(isOnThird),
                             static_cast<bool>(isOnFourth),
                             static_cast<bool>(isOnFifth),
                             static_cast<bool>(isOnSixth),
                             static_cast<bool>(isOnSeventh),
                             static_cast<bool>(isOnEighth)}});
    return true;
}

bool EasStation::writeControlTrigger(int idMaster, int mode) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeControlTrigger(mode);
    return true;
}

bool EasStation::writeProgramTrigger(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeProgramTrigger(true);
    return true;
}

bool EasStation::writeResetVme(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeResetVme();
    return true;
}

bool EasStation::writeTime(int idMaster, int hours, int min, int sec, int ms) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeTime(hours, min, sec, ms);
    return true;
}

bool EasStation::writeControlRegister(int idPaa) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) % 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]
        ->getMasters()[idMaster]
        ->getAdcs()[realIdPaa]
        ->writeControlRegister();
    return true;
}

bool EasStation::writeThreshold(int idPaa, int channel, int threshold) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) % 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]
      ->getMasters()[idMaster]
            ->getAdcs()[realIdPaa]
            ->writeThreshold(channel, threshold);
    //TODO
    hosts_[idHost]->runQueue();
    return true;
}

bool EasStation::writeDelay(int idPaa, int channel, int delay) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) % 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]->getMasters()[idMaster]->getAdcs()[realIdPaa]->writeDelay(
        channel, delay);
    return true;
}

bool EasStation::writeResetChannel(int idPaa, int channel) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) % 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]
        ->getMasters()[idMaster]
        ->getAdcs()[realIdPaa]
        ->writeResetChannel(channel);
    return true;
}

bool EasStation::writeSmoothing(int idPaa, int smoothing) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) % 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]
        ->getMasters()[idMaster]
        ->getAdcs()[realIdPaa]
        ->writeSmoothing(smoothing);
    return true;
}

bool EasStation::connectToHost(int idHost,
                               const std::string& ip,
                               int controlPort,
                               int dataPort) {
    hosts_.insert(std::pair<uint32_t, HostPtr>(
        idHost, addHost(idHost, ip, controlPort, dataPort)));
    hosts_[idHost]->connectToHost();
    return true;
}

bool EasStation::addMasterToHost(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->addMaster(realIdMaster);
    return true;
}

bool EasStation::addAdcToMaster(int idPaa) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) % 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]->getMasters()[idMaster]->addAdc(realIdPaa);
    return true;
}

bool EasStation::setTaskTable(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->initializeTable(realIdMaster - 1);	//WARNING
    return true;
}

bool EasStation::write200200(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->write200200();
    return true;
}

bool EasStation::resolutionDataZero(int idHost) {
    hosts_[idHost]->writeResolutionDataZero();
    return true;
}

bool EasStation::resolutionAndForbidOfData(int idHost, int resolution) {
    hosts_[idHost]->writeResolutionAndForbidOfData(static_cast<bool>(resolution));
    return true;
}
