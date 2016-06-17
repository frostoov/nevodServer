#ifndef REALQUEUEOFMESSAGES_HPP
#define REALQUEUEOFMESSAGES_HPP

#include <queue>
#include <memory>
#include <string>
#include <list>
#include <thread>
#include <boost/asio.hpp>

#include "../observer/observer.hpp"
#include "queueofmessages.hpp"

class RealQueueOfMessages : public QueueOfMessages {
public:
    using IoServicePtr = std::shared_ptr<boost::asio::io_service>;

	RealQueueOfMessages(const std::shared_ptr<Client>& clientReg,
						const std::shared_ptr<Client>& clientData);
	~RealQueueOfMessages();

	void update(const Subject* subject);

    void connectToHost();
    void disconnectFromHost();
	void attachToClients();
	void detachFromClients();
	void addCommandToQueue(const Record& record, ObserverPtr sender);
    void runQueue();
    void clearData();

    const Record& getRecord() const;
    Message getMessage() const;
    const std::vector<uint8_t>& getData() const;

    void write(int32_t number, bool isBan) { clientReg_->write(number, isBan); }

protected:
    void writeRegister(const Record& record);
    int fillValuesInCommandsHaveBeenDone(const std::vector<uint8_t>& data,
                                         int commandNumber);

private:
    ClientPtr clientReg_;
    ClientPtr clientData_;
    std::queue<std::pair<Record, ObserverPtr>> commandsWillBeDone_;
    std::vector<std::pair<Record, ObserverPtr>> commandsHaveBeenDone_;
    Record answerRecord_;
    Message message_;
    std::vector<uint8_t> data_;
    //	string			ip_;
};

class RealQueueOfMessagesFactory : public QueueOfMessagesFactory {
public:
	using QueueOfMessagesPtr = std::shared_ptr<RealQueueOfMessages>;

	static QueueOfMessagesPtr create(
		const std::shared_ptr<Client>& clientReg,
		const std::shared_ptr<Client>& clientData) {
		return std::make_shared<RealQueueOfMessages>(clientReg, clientData);
	}
};

#endif  // REALQUEUEOFMESSAGES_HPP
