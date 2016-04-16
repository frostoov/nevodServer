#ifndef CLIENT_H
#define CLIENT_H

#include <thread>
#include <memory>
#include <cstdint>

#include "../observer/observer.hpp"

class Client : public Subject	{
public:
	explicit Client();
	~Client();

protected:

private:

};

#endif // CLIENT_H
