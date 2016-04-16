#include "rpcserver.hpp"

RpcServer::RpcServer(uint16_t	port)
	:	xsonrpc::Server(port)	{

	xsonrpc::JsonFormatHandler	formatHandler;
	this->RegisterFormatHandler(formatHandler);

	easRpc_		= std::make_unique<EasRpc>();
	uranRpc_	= std::make_unique<UranRpc>(dispatcher_);
	easStation_	= std::make_unique<EasStation>(this->GetIoService());

	initializeDispatcherOfEasRpc();
}

RpcServer::~RpcServer()	{

}

void	RpcServer::run()	{
	this->Run();
}

void	RpcServer::initializeDispatcherOfEasRpc()	{
	auto& dispatcher = GetDispatcher();

	//	bool run = true;
	//	dispatcher_.AddMethod("exit", [&] () { run = false; }).SetHidden();

	dispatcher.AddMethod("eas_writeBanOfTimestamps",		&EasRpc::eas_writeBanOfTimestamps, *(easRpc_.get()));
	dispatcher.AddMethod("eas_writeRegisterOfMasks",		&EasRpc::eas_writeRegisterOfMasks, *(easRpc_.get()));
	dispatcher.AddMethod("eas_writeHardReset",				&EasRpc::eas_writeHardReset, *(easRpc_.get()));
	dispatcher.AddMethod("eas_writePermissionOfMasters",	&EasRpc::eas_writePermissionOfMasters, *(easRpc_.get()));
	dispatcher.AddMethod("eas_writeControlDma",				&EasRpc::eas_writeControlDma, *(easRpc_.get()));
	dispatcher.AddMethod("eas_writeStartTaskMaster",		&EasRpc::eas_writeStartTaskMaster, *(easRpc_.get()));
	dispatcher.AddMethod("eas_writeRegisterOfReadData",		&EasRpc::eas_writeRegisterOfReadData, *(easRpc_.get()));
}
