#include "realqueueofmessages.hpp"
#include <iostream>

RealQueueOfMessages::RealQueueOfMessages(const std::shared_ptr<Client>& clientReg,
								 const std::shared_ptr<Client>& clientData) {
	clientReg_ = clientReg;
	clientData_ = clientData;
}

RealQueueOfMessages::~RealQueueOfMessages() {

}

void RealQueueOfMessages::update(const Subject* subject) {
	if (subject == clientReg_.get()) {
		if (clientReg_->getMessage() == Client::Message::readyRead) {
			static size_t commandNumberBegin = 0;
			static size_t commandNumberEnd = 0;
            commandNumberEnd = fillValuesInCommandsHaveBeenDone(
                clientReg_->getData(), commandNumberBegin);
			for (size_t i = commandNumberBegin; i < commandNumberEnd; i++) {
                if (commandsHaveBeenDone_[i].first.type == Record::Type::Read) {
                    message_ = Message::recordRead;
                    answerRecord_ = commandsHaveBeenDone_[i].first;
					notify(commandsHaveBeenDone_[i].second.get());
                } else {
                    message_ = Message::recordWrite;
                    answerRecord_ = commandsHaveBeenDone_[i].first;
					notify(commandsHaveBeenDone_[i].second.get());
                }
            }
            commandNumberBegin = commandNumberEnd;
            if (commandsHaveBeenDone_.empty() == true) {
                commandNumberBegin = 0;
                commandNumberEnd = 0;
            }
        }

		if (clientReg_->getMessage() == Client::Message::connected) {
            message_ = Message::connected;
            notify();
        }

		if (clientReg_->getMessage() == Client::Message::disconnected) {
            message_ = Message::disconnected;
            notify();
        }

		if (clientReg_->getMessage() == Client::Message::error) {
            message_ = Message::error;
            notify();
        }
    }

	if (subject == clientData_.get()) {
		if (clientData_->getMessage() == Client::Message::readyRead) {
            static int packetCount = 0;
            message_ = Message::dataRead;
            if (packetCount < 200) {
                data_.insert(data_.end(), clientData_->getData().begin(),
                             clientData_->getData().end());
                packetCount++;
            }
            if (packetCount == 200) {
                packetCount = 0;
                notify();
                data_.insert(data_.end(), clientData_->getData().begin(),
                             clientData_->getData().end());
            }
        }
    }
}

void RealQueueOfMessages::connectToHost() {
    clientReg_->connectToHost();
    clientData_->connectToHost();
}

void RealQueueOfMessages::disconnectFromHost() {
    clientReg_->disconnectFromHost();
    clientData_->disconnectFromHost();
}

void RealQueueOfMessages::attachToClients()	{
	clientReg_->attach(this);
	clientData_->attach(this);
}

void RealQueueOfMessages::detachFromClients()	{
	clientReg_->detach(this);
	clientData_->detach(this);
}

void RealQueueOfMessages::addCommandToQueue(const Record& record,
                                        ObserverPtr sender) {
    commandsWillBeDone_.push(std::pair<Record, ObserverPtr>(record, sender));
}

void RealQueueOfMessages::runQueue() {
    while (!commandsWillBeDone_.empty()) {
        writeRegister(commandsWillBeDone_.front().first);
        commandsHaveBeenDone_.push_back(commandsWillBeDone_.front());
        commandsWillBeDone_.pop();
    }
}

void RealQueueOfMessages::writeRegister(const Record& record) {
    if (record.type == Record::Type::Zero)
        clientReg_->writeRegister3000(record.address, record.value);
    if (record.type == Record::Type::Two)
        clientReg_->writeRegister3002(record.address, record.value);
    if (record.type == Record::Type::Read)
        clientReg_->readRegister(record.address);
    if (record.type == Record::Type::Sleep)
        std::this_thread::sleep_for(std::chrono::milliseconds(record.address));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

int RealQueueOfMessages::fillValuesInCommandsHaveBeenDone(
    const std::vector<uint8_t>& data,
    int commandNumber) {
    int command = commandNumber;
	for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == 0x0b && data[i + 1] == 0xb9 && data[i + 2] == 0x0b &&
            data[i + 3] == 0xb9) {
            uint16_t value = data[i + 10] << 8;
            value += data[i + 11];
            commandsHaveBeenDone_[commandNumber].first.value = value;
            command++;
        }

        if (data[i] == 0x0b && data[i + 1] == 0xb8 && data[i + 2] == 0x0b &&
            data[i + 3] == 0xb8) {
            uint16_t value = data[i + 8] << 8;
            value += data[i + 9];
            commandsHaveBeenDone_[commandNumber].first.value = value;
            command++;
        }

        if (data[i] == 0x0b && data[i + 1] == 0xba && data[i + 2] == 0x0b &&
            data[i + 3] == 0xba) {
            uint16_t value = data[i + 8] << 8;
            value += data[i + 9];
            commandsHaveBeenDone_[commandNumber].first.value = value;
            command++;
        }
    }

    return command;
}

void RealQueueOfMessages::clearData() {
    clientData_->clearData();
    data_.clear();
}

const Record& RealQueueOfMessages::getRecord() const {
    return answerRecord_;
}

RealQueueOfMessages::Message RealQueueOfMessages::getMessage() const {
    return message_;
}

const std::vector<uint8_t>& RealQueueOfMessages::getData() const {
    return data_;
}
