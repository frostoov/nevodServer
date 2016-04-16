#ifndef URANRPC_H
#define URANRPC_H

#include "dispatcher.hpp"

class UranRpc	{
public:
	explicit UranRpc(xsonrpc::Dispatcher& dispatcher);
	~UranRpc();

protected:
	void	initializeDispatcher();

private:
	xsonrpc::Dispatcher&	dispatcher_;
};

#endif//URANRPC_H
