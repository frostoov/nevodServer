#include "server/rpcserver.hpp"

int main(int argc, char *argv[])	{
	RpcServer	server(2222);
	server.start();
	return 0;
}
