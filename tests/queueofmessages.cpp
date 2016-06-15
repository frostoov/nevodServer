#include <memory>
#include <catch.hpp>

#include "../src/eas/realqueueofmessages.hpp"
#include "mocks/clientmock.hpp"


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

	SECTION("") {

	}
}
