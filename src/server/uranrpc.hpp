#ifndef URANRPC_H
#define URANRPC_H

#include "rpcserver/dispatcher.hpp"

class UranRpc	{
public:
	explicit UranRpc(Dispatcher& dispatcher);
	~UranRpc();

protected:
	void	initializeDispatcher();

private:
	Dispatcher&	dispatcher_;
};

#endif//URANRPC_H
