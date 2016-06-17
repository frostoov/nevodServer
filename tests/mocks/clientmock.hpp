#ifndef CLIENTFAKE_HPP
#define CLIENTFAKE_HPP

#include "../src/eas/client.hpp"
#include "../src/eas/registers.hpp"

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
		finishedQueue_.push_back(Record{address, 0x0, Record::Type::Read});
	}

	void writeRegister3000(uint32_t address, uint16_t data) {
		finishedQueue_.push_back(Record{address, data, Record::Type::Zero});
	}

	void writeRegister3002(uint32_t address, uint16_t data) {
		finishedQueue_.push_back(Record{address, data, Record::Type::Zero});
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

	const std::list<Record>& getFinishedQueue() const {
		return finishedQueue_;
	}

	void clearFinishedQueue() {
		finishedQueue_.clear();
	}

private:
	std::list<Record> finishedQueue_;

};

#endif//CLIENTFAKE_HPP
