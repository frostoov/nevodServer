#ifndef CLIENTTORPCSERVER_HPP
#define CLIENTTORPCSERVER_HPP

#include <fakeit.hpp>
#include <cstdint>

class VirtualClientToRpcServer {
public:
	static VirtualClientToRpcServer& fakeIt();

	virtual bool connectClientToServer(const std::string& ip,
									   uint16_t controlPort,
									   uint16_t dataPort) = 0;
	virtual void disconnectClientFromServer() = 0;
	virtual bool connectServerToHost(uint16_t hostNumber,
									 const std::string& hostIp) = 0;
	virtual void disconnectServerFromHost(uint16_t hostId) = 0;
};

#endif//CLIENTTORPCSERVER_HPP
