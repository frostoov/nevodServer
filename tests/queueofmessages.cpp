#include <memory>
#include <catch.hpp>

#include <iostream>

#include "../src/eas/realqueueofmessages.hpp"
#include "../src/eas/registers.hpp"
#include "mocks/clientmock.hpp"
#include "mocks/hostmock.hpp"

TEST_CASE("Queue Of Messages") {
	auto clientReg = std::make_shared<ClientMock>();
	auto clientData = std::make_shared<ClientMock>();
	auto queue = RealQueueOfMessagesFactory::create(clientReg, clientData);

	SECTION("Attaching to clients and detaching from them") {
		queue->attachToClients();
		REQUIRE(clientReg->isAttach(queue.get()) == true);
		REQUIRE(clientData->isAttach(queue.get()) == true);

		queue->detachFromClients();
		REQUIRE(clientReg->isAttach(queue.get()) == false);
		REQUIRE(clientData->isAttach(queue.get()) == false);
	}

	SECTION("Does QueueOfMessages's work correctly") {
		std::shared_ptr<HostMock> host = std::make_shared<HostMock>(queue);
		std::list<Record> queueForWriting = {
			Record{0x1, 0x11, Record::Type::Zero},
			Record{0x2, 0x12, Record::Type::Two},
			Record{0x3, 0x0, Record::Type::Read},
			Record{0x4, 0x14, Record::Type::Two}};

		for (auto& record : queueForWriting)
			host->addCommandToQueueTest(record);
		queue->runQueue();
		auto resultQueue = clientReg->getFinishedQueue();
		REQUIRE((queueForWriting == resultQueue));
	}

	SECTION("Testing update function") {
		//TODO
	}
}
