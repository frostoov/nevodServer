#ifndef CLIENTTORPCSERVER_HPP
#define CLIENTTORPCSERVER_HPP

#include <fakeit.hpp>
#include <cstdint>

class VirtualClientToRpcServer {
public:
	static VirtualClientToRpcServer& fakeIt();
};

#endif  // CLIENTTORPCSERVER_HPP
