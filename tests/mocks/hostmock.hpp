#ifndef HOSTMOCK_HPP
#define HOSTMOCK_HPP

#include "../src/observer/observer.hpp"
#include "../src/eas/queueofmessages.hpp"

class HostMock : public Observer,
				 public std::enable_shared_from_this<HostMock> {
public:
	using QueuePtr = std::shared_ptr<QueueOfMessages>;

	HostMock(const std::shared_ptr<QueueOfMessages>& queue) : queue_(queue) {
		queue_->attach(this);
		queue_->attachToClients();
	}

	~HostMock() { queue_->detachFromClients(); }

	void update(const Subject* subject) {}

	void addCommandToQueueTest(const Record& record) {
		queue_->addCommandToQueue(record, shared_from_this());
	}

private:
	QueuePtr queue_;
};

#endif  // HOSTMOCK_HPP
