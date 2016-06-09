#ifndef CLIENTFAKE_HPP
#define CLIENTFAKE_HPP

#include <fakeit.hpp>

#include "../src/eas/client.hpp"

class ClientFake : public Client {
public:

	ClientFake(const std::string& ip,
			   uint16_t port,
			   const IoServicePtr& service)
		:	Client(ip, port, service)	{

	}

	bool connectToHost() {
		std::cout << "Connected to Host" << std::endl;
		return true;
	}

//	ClientFake(const ClientFake&) = delete;

//	static ClientFake& create() {
//		fakeit::Mock<ClientFake> mock;
//		fakeit::When(Method(mock, fuck)).Return(1);
//		return mock.get();
//	}

};

#endif//CLIENTFAKE_HPP
