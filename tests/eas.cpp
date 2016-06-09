#include <catch.hpp>

#include "../src/eas/queueofmessages.hpp"
#include "mocks/clientfake.hpp"

TEST_CASE("Queue Of Messages") {
//	auto fakeFirst = ClientFake::create();
//	auto fakeSecond = ClientFake::create();
	std::shared_ptr<boost::asio::io_service> service =
			std::make_shared<boost::asio::io_service>();
	auto fakeFirst = std::make_shared<ClientFake>("127.0.0.1",
												  2222,
												  service);
	auto fakeSecond = std::make_shared<ClientFake>("127.0.0.1",
												   2222,
												   service);
	QueueOfMessages clientQueue(fakeFirst, fakeSecond);
	clientQueue.connectToHost();
	std::cout << "I am here!!!" << std::endl;
	REQUIRE(1 == 1);
}
