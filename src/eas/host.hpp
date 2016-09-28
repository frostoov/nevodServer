#ifndef HOST_H
#define HOST_H

#include <vector>
#include <cstdint>
#include <memory>
#include <array>
#include <boost/asio.hpp>

#include "master.hpp"
#include "registers.hpp"
#include "queueofmessages.hpp"

class Host : public Subject,
			 public Observer,
			 public std::enable_shared_from_this<Host> {
public:
	using MasterPtr = std::shared_ptr<Master>;
	using QueuePtr = std::shared_ptr<QueueOfMessages>;
    using IoServicePtr = std::shared_ptr<boost::asio::io_service>;

	Host(const std::shared_ptr<QueueOfMessages>& clientQueue);
    ~Host();

	void update(const Subject* subject);

    MasterPtr addMaster(uint32_t numberMaster);
    void deleteMaster(uint32_t numberMaster);
    void connectToHost();       //
    void disconnectFromHost();  //
    void readState();
    void runQueue();

    void writeBanOfTimestamps(bool ban);
    void writeTestRegister(uint16_t data);
    void writeCoarseReset(const std::array<bool, 4>& resetLink);
    void writeResolutionOfLinks(const std::array<bool, 4>& resolutionLink);
    void writeExchangeRegister(uint16_t data);
    void writeControlDma(int oneOnTwoReset);
    void writeClusterNumberLink(uint32_t numberLink, uint16_t numberCluster);
    void writeStartTaskLink(uint32_t numberLink, uint32_t numberBank);
    void writeRegisterOfReadData(const std::array<bool, 4>& readLink);
    void writeResolutionAndForbidOfData(bool resolution);
    void writeClearDataBuffer(bool clear);

    void initializeTable(uint32_t numberMaster,
                         const std::vector<uint32_t>& numbersOfChannels);
    void initializeTable(uint32_t numberMaster);
    void writeSleep(uint32_t milliseconds);

    void write(int32_t number, bool isBan) {
        clientQueue_->write(number, isBan);
    }

    QueuePtr getQueue();
    Record getResult() const;
    HostRegisters getRegisters() const;
    std::map<uint32_t, MasterPtr> getMasters() const;

    void writeRegister(uint32_t address, uint32_t data, Record::Type type);
    void readRegister(uint32_t address);

protected:
    Record getRecordWithOffset(Record record);

private:
    QueuePtr clientQueue_;
    std::map<uint32_t, MasterPtr> masters_;
    HostRegisters registers_;
    uint32_t offset_;
    Record resultRecord_;
};

#endif  // HOST_H
