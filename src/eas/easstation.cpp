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
	auto clientQueue = RealQueueOfMessagesFactory::create(clientReg, clientData);
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

bool EasStation::writeRegisterOfMasks(int idHost) {}

bool EasStation::writeHardReset(int idMaster) {}

bool EasStation::writePermissionOfMasters(int idMaster, bool isOpen) {}

bool EasStation::writeControlDma(int idHost, bool isOn) {}

bool EasStation::writeStartTaskMaster(int idMaster) {}

bool EasStation::writeRegisterOfReadData(int idHost) {}
