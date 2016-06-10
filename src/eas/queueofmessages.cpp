#include "queueofmessages.hpp"
#include <iostream>

QueueOfMessages::QueueOfMessages(const std::shared_ptr<HostClient>& clientReg,
								 const std::shared_ptr<HostClient>& clientData) {
	clientReg_ = clientReg;
	clientData_ = clientData;

    clientReg_->attach(this);
    clientData_->attach(this);
}

QueueOfMessages::~QueueOfMessages() {
    clientReg_->detach(this);
    clientData_->detach(this);
}

void QueueOfMessages::update(const Subject* subject) {
    if (subject == clientReg_.get()) {
        if (clientReg_->getMessage() == HostClient::Message::readyRead) {
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

        if (clientReg_->getMessage() == HostClient::Message::connected) {
            message_ = Message::connected;
            notify();
        }

        if (clientReg_->getMessage() == HostClient::Message::disconnected) {
            message_ = Message::disconnected;
            notify();
        }

        if (clientReg_->getMessage() == HostClient::Message::error) {
            message_ = Message::error;
            notify();
        }
    }

    if (subject == clientData_.get()) {
        if (clientData_->getMessage() == HostClient::Message::readyRead) {
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

void QueueOfMessages::connectToHost() {
    clientReg_->connectToHost();
    clientData_->connectToHost();
}

void QueueOfMessages::disconnectFromHost() {
    clientReg_->disconnectFromHost();
    clientData_->disconnectFromHost();
}

void QueueOfMessages::addCommandToQueue(const Record& record,
                                        ObserverPtr sender) {
    commandsWillBeDone_.push(std::pair<Record, ObserverPtr>(record, sender));
}

void QueueOfMessages::runQueue() {
    while (!commandsWillBeDone_.empty()) {
        writeRegister(commandsWillBeDone_.front().first);
        commandsHaveBeenDone_.push_back(commandsWillBeDone_.front());
        commandsWillBeDone_.pop();
    }
}

void QueueOfMessages::writeRegister(const Record& record) {
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

int QueueOfMessages::fillValuesInCommandsHaveBeenDone(
    const std::vector<uint8_t>& data,
    int commandNumber) {
    //	for (auto& item : commandsHaveBeenDone_)
    //		item.first.value = 13232;
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

void QueueOfMessages::clearData() {
    clientData_->clearData();
    data_.clear();
}

const Record& QueueOfMessages::getRecord() const {
    return answerRecord_;
}

QueueOfMessages::Message QueueOfMessages::getMessage() const {
    return message_;
}

const std::vector<uint8_t>& QueueOfMessages::getData() const {
    return data_;
}
