#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <json.hpp>

#include "testclasses/rpcservertest.hpp"

using nlohmann::json;

TEST_CASE("Server answers correctly", "[server answers]") {
	RpcServerTest server(2222);  // any port is suitable
	auto connection = server.getTcpConnectionTest();
	auto message =
		"{\"jsonrpc\": \"2.0\","
		"\"method\": \"plusTwoNumbers\","
		"\ \"params\": [23, 23],"
		"\"id\": 1}";
	json answer;
	REQUIRE_NOTHROW(answer =
						json::parse(connection->answerToRequestTest(message)));
	REQUIRE(answer["result"].get<int>() == 46);
}
