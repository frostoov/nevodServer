#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cstdint>
#include <string>
#include <memory>

class Client {
public:
	virtual bool connectToHost() = 0;
	virtual bool disconnectFromHost() = 0;
	virtual void readRegister(uint32_t address) = 0;
	virtual void writeRegister3000(uint32_t address, uint32_t data) = 0;
	virtual void writeRegister3002(uint32_t address, uint32_t data) = 0;

	virtual ~Client() {}
};

class ClientFactory {
public:
	using ClientPtr = std::shared_ptr<Client>;

	virtual ClientPtr create(const std::string& ip, uint16_t port) = 0;

	virtual ~ClientFactory() {}
};

#endif//CLIENT_HPP
