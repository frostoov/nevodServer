#ifndef QUEUEOFMESSAGES_HPP
#define QUEUEOFMESSAGES_HPP

#include <queue>
#include <memory>
#include <string>
#include <list>
#include <boost/asio.hpp>

#include "../observer/observer.hpp"
#include "client.hpp"
#include "registers.hpp"

class QueueOfMessages : public Observer,
                        public Subject,
                        public std::enable_shared_from_this<QueueOfMessages> {
public:
    using ClientPtr = std::shared_ptr<Client>;
    using ObserverPtr = std::shared_ptr<Observer>;
    using IoServicePtr = std::shared_ptr<boost::asio::io_service>;

    enum class Message {
        connected,
        disconnected,
        recordRead,
        recordWrite,
        dataRead,
        error,
        null
    };

	QueueOfMessages(const std::shared_ptr<Client>& clientReg,
					const std::shared_ptr<Client>& clientData);
    ~QueueOfMessages();

    void update(const Subject* subject);

    void connectToHost();
    void disconnectFromHost();
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

class QueueOfMessagesFactory {
public:
	using QueueOfMessagesPtr = std::shared_ptr<QueueOfMessages>;

	static QueueOfMessagesPtr create(
		const std::shared_ptr<Client>& clientReg,
		const std::shared_ptr<Client>& clientData) {
		return std::make_shared<QueueOfMessages>(clientReg, clientData);
	}
};

#endif  // QUEUEOFMESSAGES_HPP
