#ifndef CLIENTFAKE_HPP
#define CLIENTFAKE_HPP

#include <fakeit.hpp>

#include "../src/eas/client.hpp"

class ClientFake : public Client {
public:

//	static ClientFake& create() {
//		fakeit::Mock<ClientFake> mock;
//		fakeit::When(Method(mock, fuck)).Return(1);
//		return mock.get();
//	}

};

#endif//CLIENTFAKE_HPP
