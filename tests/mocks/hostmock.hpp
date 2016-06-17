#ifndef HOSTMOCK_HPP
#define HOSTMOCK_HPP

#include "../src/observer/observer.hpp"
#include "../src/eas/queueofmessages.hpp"

class HostMock : public Observer, std::enable_shared_from_this<HostMock> {
public:
	using QueuePtr = std::shared_ptr<QueueOfMessages>;

	HostMock(const QueuePtr queue)
		:	queue_(queue) {
		queue->attach(this);
		queue->attachToClients();
	}

	~HostMock() {
		queue_->detachFromClients();
	}

	void update(const Subject* subject) {

	}

	void addCommandToQueueTest(const Record& record) {
		queue_->addCommandToQueue(record, shared_from_this());
	}

private:
	QueuePtr queue_;
};

#endif//HOSTMOCK_HPP
