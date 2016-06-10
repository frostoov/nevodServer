#include <catch.hpp>

#include "../src/eas/queueofmessages.hpp"
#include "mocks/clientfake.hpp"

Client& createFakeClient() {
	fakeit::Mock<Client> mock;
	fakeit::When(Method(mock, connectToHost)).Return(true);
	return mock.get();
}

TEST_CASE("Queue Of Messages") {
	Client& clientFakeFirst = createFakeClient();
	Client& clientFakeSecond = createFakeClient();
	QueueOfMessages clientQueue(clientFakeFirst, clientFakeSecond);
	clientQueue.connectToHost();
	std::cout << "I am here!!!" << std::endl;
	REQUIRE(1 == 1);
}
