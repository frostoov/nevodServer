#ifndef EASRPC_H
#define EASRPC_H

#include <cstdint>
#include <string>
#include <memory>
#include <boost/asio.hpp>

#include "../eas/easstation.hpp"

class EasRpc	{
public:	
	using EasStationPtr	= std::unique_ptr<EasStation>;
	using IoServicePtr	= std::shared_ptr<boost::asio::io_service>;

	explicit EasRpc(const IoServicePtr& service);
	~EasRpc();

	bool	eas_writeBanOfTimestamps(int32_t idHost, bool isBan);
	bool	eas_writeRegisterOfMasks(int idHost);
	bool	eas_writeHardReset(int idMaster);
	bool	eas_writePermissionOfMasters(int idMaster, bool isOpen);
	bool	eas_writeControlDma(int idHost, bool	isOn);
	bool	eas_writeStartTaskMaster(int idMaster);
	bool	eas_writeRegisterOfReadData(int idHost);

protected:

private:
	EasStationPtr	easStation_;
};

#endif//EASRPC_H
