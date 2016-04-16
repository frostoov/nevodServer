#ifndef EASSTATION_H
#define EASSTATION_H

#include <memory>
#include <boost/asio.hpp>

class EasStation	{
public:
	using IoServicePtr	= std::shared_ptr<boost::asio::io_service>;

	explicit EasStation(const IoServicePtr&	service)	{

	}

	~EasStation()	{}

protected:

private:
	IoServicePtr	service_;
};

#endif//EASSTATION_H
