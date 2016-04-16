#include "rpcserver/rpcserver.hpp"


int main(int argc, char *argv[])	{
	RpcServer	server(2222);
	server.run();
	return 0;
}
