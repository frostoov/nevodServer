#include "clienttorpcserver.hpp"

using namespace fakeit;

VirtualClientToRpcServer& VirtualClientToRpcServer::fakeIt() {
	Mock<VirtualClientToRpcServer> mock;
	When(Method(mock, connectClientToServer)).AlwaysReturn(true);
}
