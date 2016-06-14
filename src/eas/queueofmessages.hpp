#ifndef QUEUEOFMESSAGES_HPP
#define QUEUEOFMESSAGES_HPP

#include <memory>

#include "../observer/observer.hpp"
#include "client.hpp"
#include "registers.hpp"

class QueueOfMessages : public Observer, public Subject {
public:
	using ClientPtr = std::shared_ptr<Client>;
	using ObserverPtr = std::shared_ptr<Observer>;

	enum class Message {
		connected,
		disconnected,
		recordRead,
		recordWrite,
		dataRead,
		error,
		null
	};

	virtual void attachToClients() = 0;
	virtual void detachFromClients() = 0;
	virtual void connectToHost() = 0;
	virtual void disconnectFromHost() = 0;
	virtual void addCommandToQueue(const Record& record, ObserverPtr sender) = 0;
	virtual void runQueue() = 0;
	virtual void clearData() = 0;

	virtual const Record& getRecord() const = 0;
	virtual Message getMessage() const = 0;
	virtual const std::vector<uint8_t>& getData() const = 0;

	//TODO
	virtual void write(int32_t number, bool isBan) = 0;

	virtual ~QueueOfMessages() {}
};

class QueueOfMessagesFactory {
public:
	using QueueOfMessagesPtr = std::shared_ptr<QueueOfMessages>;
	using ClientPtr = std::shared_ptr<Client>;

	virtual QueueOfMessagesPtr create(const ClientPtr clientReg,
									  const ClientPtr clientData) = 0;
};

#endif  // QUEUEOFMESSAGES_HPP
