#include "easstation.hpp"

EasStation::EasStation(const IoServicePtr& service) : service_(service) {
    //    auto host = addHost(0, "127.0.0.1", 2223, 2224);
    //    host->connectToHost();
}

EasStation::~EasStation() {}

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

bool EasStation::writeBanOfTimestamps(int32_t idHost, bool isBan) {
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
}

bool EasStation::writePermissionOfMasters(int idMaster, bool isOpen) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    //    hosts_[idHost]->getMasters()[realIdMaster]->write
}

bool EasStation::writeControlDma(int idHost, bool isOn) {
    hosts_[idHost]->writeControlDma(isOn);
}

bool EasStation::writeStartTaskMaster(int idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    //    hosts_[idHost]->getMasters()[idMaster]-
}

bool EasStation::writeRegisterOfReadData(uint32_t idHost,
                                         bool isOnFirst,
                                         bool isOnSecond,
                                         bool isOnThird,
                                         bool isOnFourth) {
    hosts_[idHost]->writeRegisterOfReadData(
        std::array<bool, 4>{{isOnFirst, isOnSecond, isOnThird, isOnFourth}});
}

bool EasStation::writePermissionOfData(uint32_t idHost,
                                       bool isOnFirst,
                                       bool isOnSecond,
                                       bool isOnThird,
                                       bool isOnFourth) {
    hosts_[idHost]->writeResolutionOfLinks(
        std::array<bool, 4>{{isOnFirst, isOnSecond, isOnThird, isOnFourth}});
}

bool EasStation::writeClearDataBuffer(int idHost) {
    hosts_[idHost]->writeClearDataBuffer(true);
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
}

bool EasStation::writeSetCoincidence(uint32_t idMaster, uint32_t coincidence) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[idMaster]->writeCoincidence(coincidence);
}

bool EasStation::writeResetCounter(uint32_t idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeResetCounter();
}

bool EasStation::writeSetTimeGate(uint32_t idMaster, int ns) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    uint16_t window = 0;  // TODO ns to window
    hosts_[idHost]->getMasters()[realIdMaster]->writeTemporaryWindow(window);
}

bool EasStation::writeActiveChannels(uint32_t idMaster,
                                     bool isOnFirst,
                                     bool isOnSecond,
                                     bool isOnThird,
                                     bool isOnFourth,
                                     bool isOnFifth,
                                     bool isOnSixth,
                                     bool isOnSeventh,
                                     bool isOnEighth) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeMaskOfActiveChannels(
        std::array<bool, 8>{{isOnFirst, isOnSecond, isOnThird, isOnFourth,
                             isOnFifth, isOnSixth, isOnSeventh, isOnEighth}});
}

bool EasStation::writeControlTrigger(uint32_t idMaster, int mode) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeControlTrigger(mode);
}

bool EasStation::writeProgramTrigger(uint32_t idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeProgramTrigger(true);
}

bool EasStation::writeResetVme(uint32_t idMaster) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeResetVme();
}

bool EasStation::writeTime(uint32_t idMaster,
                           int hours,
                           int min,
                           int sec,
                           int ms) {
    uint32_t idHost = static_cast<uint32_t>(idMaster) / 10;
    uint32_t realIdMaster = idMaster % 10;
    hosts_[idHost]->getMasters()[realIdMaster]->writeTime(hours, min, sec, ms);
}

bool EasStation::writeControlRegister(uint32_t idPaa) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) & 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]
        ->getMasters()[idMaster]
        ->getAdcs()[realIdPaa]
        ->writeControlRegister();
}

bool EasStation::writeThreshold(uint32_t idPaa, uint16_t threshold) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) & 10;
    uint32_t realIdPaa = idPaa % 10;
    for (uint32_t i = 0; i < 2; i++)
        hosts_[idHost]
            ->getMasters()[idMaster]
            ->getAdcs()[realIdPaa]
            ->writeThreshold(i, threshold);
}

bool EasStation::writeDelay(uint32_t idPaa, uint32_t channel, uint16_t delay) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) & 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]->getMasters()[idMaster]->getAdcs()[realIdPaa]->writeDelay(
        channel, delay);
}

bool EasStation::writeResetChannel(uint32_t idPaa, uint32_t channel) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) & 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]
        ->getMasters()[idMaster]
        ->getAdcs()[realIdPaa]
        ->writeResetChannel(channel);
}

bool EasStation::writeSmoothing(uint32_t idPaa, uint16_t smoothing) {
    uint32_t idHost = static_cast<uint32_t>(idPaa) / 100;
    uint32_t idMaster = (idPaa / 10) & 10;
    uint32_t realIdPaa = idPaa % 10;
    hosts_[idHost]
        ->getMasters()[idMaster]
        ->getAdcs()[realIdPaa]
        ->writeSmoothing(smoothing);
}
