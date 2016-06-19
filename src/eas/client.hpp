#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

#include "../observer/observer.hpp"

class Client : public Subject {
public:
	enum class Message { connected, disconnected, readyRead, error, null };

    virtual ~Client() {}

	virtual bool connectToHost() = 0;
	virtual bool disconnectFromHost() = 0;
	virtual void readRegister(uint32_t address) = 0;
	virtual void writeRegister3000(uint32_t address, uint16_t data) = 0;
	virtual void writeRegister3002(uint32_t address, uint16_t data) = 0;
	virtual void clearData() = 0;

	virtual const std::vector<uint8_t>& getData() const = 0;
	virtual Message getMessage() const = 0;

	//TODO
	virtual void write(int32_t number, bool isBan) = 0;
};

class ClientFactory {
public:
	using ClientPtr = std::shared_ptr<Client>;

	virtual ClientPtr create(const std::string& ip, uint16_t port) = 0;

	virtual ~ClientFactory() {}
};

#endif//CLIENT_HPP
