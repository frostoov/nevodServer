#include "server/server.hpp"

#include "configparsers/stationconfig.hpp"

#include "eas/easstation.hpp"

int main(int argc, char* argv[]) {
    //    Server server(2222);
    //    server.start();

        auto service = std::make_shared<boost::asio::io_service>();
        EasStation station(service);
        auto host = station.addHost(0, "192.168.1.40", 3000, 3007);
        service->run();
        host->connectToHost();


//    StationConfig config;
//    config.addHost("my_host");
//    config.addJsonPairToHost(
//        "my_host", StationConfig::JsonPair({{"method", "this_is_a_method"},
//                                            {"params", {1, 2, 3}}}));
//    config.addJsonPairToHost(
//        "second_host", StationConfig::JsonPair({{"method", "dsdd"},
//                                            {"params", {3, 3, 3}}}));
//    config.writeToConfig("config.json");
    return 0;
}
