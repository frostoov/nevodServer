#include "easrpc.hpp"

#include <iostream>	//TODO

EasRpc::EasRpc(const IoServicePtr& service)	{
	easStation_	= std::make_unique<EasStation>(service);
}

EasRpc::~EasRpc()	{

}

bool EasRpc::eas_writeBanOfTimestamps(int32_t idHost, bool isBan)	{
	std::cout << "I have been invoked\t" << isBan << std::endl;
	return false;
}

bool EasRpc::eas_writeRegisterOfMasks(int idHost)	{

}

bool EasRpc::eas_writeHardReset(int idMaster)	{

}

bool EasRpc::eas_writePermissionOfMasters(int idMaster, bool isOpen)	{

}

bool EasRpc::eas_writeControlDma(int idHost, bool isOn)	{

}

bool EasRpc::eas_writeStartTaskMaster(int idMaster)	{

}

bool EasRpc::eas_writeRegisterOfReadData(int idHost)	{

}
