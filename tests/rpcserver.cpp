#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <json.hpp>

using nlohmann::json;

TEST_CASE("Server answers correctly", "[server answers]") {

//    RpcServerTest server(2222);  // any port is suitable
//    auto connection = server.getTcpConnectionTest();
//    json answer;
//    std::string message;

//    SECTION("Valid requests") {
//        message =
//            "{\"jsonrpc\": \"2.0\","
//            "\"method\": \"plusTwoNumbers\","
//            "\"params\": [23, 23],"
//            "\"id\": 1}";
//        REQUIRE_NOTHROW(
//            answer = json::parse(connection->answerToRequestTest(message)));
//        REQUIRE(answer["result"].get<int>() == 46);

//        message =
//            "{\"jsonrpc\": \"2.0\","
//            "\"method\": \"concatTwoStrings\","
//            "\"params\": [\"hello \", \"world\"],"
//            "\"id\": 2}";
//        REQUIRE_NOTHROW(
//            answer = json::parse(connection->answerToRequestTest(message)));
//        REQUIRE(answer["result"].get<std::string>() ==
//                std::string("hello world"));
//    }

//    SECTION("Call of non-existent method") {
//        message =
//            "{\"jsonrpc\": \"2.0\","
//            "\"method\": \"non-existentMethod\","
//            "\"params\": [123],"
//            "\"id\": 1}";
//        REQUIRE_THROWS(
//            answer = json::parse(connection->answerToRequestTest(message)));
//    }

//    SECTION("Call with invalid JSON") {
//        message =
//            "{\"jsonrpc\": \"2.0\","
//            "\"method\": \"plusTwoNumbers\","
//            "\"params\": [23, 23]" // comma is missed
//            "\"id\": 1}";
//        REQUIRE_THROWS(
//            answer = json::parse(connection->answerToRequestTest(message)));
//    }
}
