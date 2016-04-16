#ifndef URANRPC_H
#define URANRPC_H

#include <include/xsonrpc/dispatcher.h>

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
