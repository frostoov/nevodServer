#ifndef CLIENTFAKE_HPP
#define CLIENTFAKE_HPP

#include "../src/eas/client.hpp"

class ClientMock : public Client {
public:

	ClientMock() {}
	~ClientMock() {}

	bool connectToHost() {
		return true;
	}

	bool disconnectFromHost() {
		return true;
	}

	void readRegister(uint32_t address) {

	}

	void writeRegister3000(uint32_t address, uint32_t data) {

	}

	void writeRegister3002(uint32_t address, uint32_t data) {

	}

	void clearData() {

	}

	const std::vector<uint8_t>& getData() const {
		return std::vector<uint8_t>{1, 2, 3, 4};
	}

	Message getMessage() const {
		return Message::connected;
	}

	void write(int32_t number, bool isBan) {

	}

};

#endif//CLIENTFAKE_HPP
