#include "easstation.hpp"

EasStation::EasStation(const IoServicePtr &service)
	:	service_(service)	{

}

EasStation::~EasStation()	{

}

EasStation::HostPtr EasStation::addHost(uint32_t numberHost, const std::string &ip)	{
	HostPtr	host = std::make_shared<Host>(ip, service_);
	hosts_.insert(std::pair<uint32_t, HostPtr>(numberHost, host));
	return	host;
}

void EasStation::deleteHost(uint32_t numberHost)	{
	hosts_.erase(numberHost);
}

bool EasStation::writeBanOfTimestamps(int32_t idHost, bool isBan)	{
	hosts_[idHost]->writeBanOfTimestamps(isBan);						//TODO they have to return bool values
}

bool EasStation::writeRegisterOfMasks(int idHost)	{

}

bool EasStation::writeHardReset(int idMaster)	{

}

bool EasStation::writePermissionOfMasters(int idMaster, bool isOpen)	{

}

bool EasStation::writeControlDma(int idHost, bool isOn)	{

}

bool EasStation::writeStartTaskMaster(int idMaster)	{

}

bool EasStation::writeRegisterOfReadData(int idHost)	{

}
