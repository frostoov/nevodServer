#include "server/rpcserver.hpp"

#include "eas/easstation.hpp"

int main(int argc, char *argv[])	{
//	RpcServer	server(2222);
//	server.start();

	auto service = std::make_shared<boost::asio::io_service>();
	EasStation station(service);
	auto host = station.addHost(0, "127.0.0.1");
	host->connectToHost();
	service->run();
	return 0;
}
