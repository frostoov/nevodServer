#include "server/server.hpp"

#include "eas/easstation.hpp"

int main(int argc, char* argv[]) {
	Server server(2222);
	server.start();

	//	auto service = std::make_shared<boost::asio::io_service>();
	//	EasStation station(service);
	//	auto host = station.addHost(0, "127.0.0.1");
	//	host->connectToHost();
	//	host->write();
	//	service->run();
	return 0;
}
