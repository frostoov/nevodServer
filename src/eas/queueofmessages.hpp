#ifndef STACKOFMESSAGES_H
#define STACKOFMESSAGES_H

#include <queue>
#include <memory>
#include <string>
#include <list>
#include <boost/asio.hpp>

#include "../observer/observer.hpp"
#include "client.hpp"
#include "registers.hpp"

class QueueOfMessages : public Observer, public Subject,
		public std::enable_shared_from_this<QueueOfMessages>	{
public:
	using	ClientPtr		= std::shared_ptr<Client>;
	using	ObserverPtr		= std::shared_ptr<Observer>;
	using	IoServicePtr	= std::shared_ptr<boost::asio::io_service>;

	enum class Message	{
		connected,
		disconnected,
		recordRead,
		recordWrite,
		dataRead,
		error,
		null
	};

	QueueOfMessages(const std::string& ip, uint16_t registerPort,
					uint16_t dataPort, const IoServicePtr& service);
	~QueueOfMessages();

	void	update(const Subject*	subject);

	void	connectToHost();
	void	disconnectFromHost();
	void	addCommandToStack(const Record&	record, ObserverPtr	sender);
	void	runQueue();
	void	clearData();

	const Record&					getRecord()		const;
	Message							getMessage()	const;
	const std::vector<uint8_t>&	getData()			const;

	void	write(int32_t number, bool isBan)	{
		clientReg_->write(number, isBan);
	}

protected:
	void	writeRegister(const Record&	record);
	int		fillValuesInCommandsHaveBeenDone(const std::vector<uint8_t>& data,
											 int commandNumber);

private:
	ClientPtr									clientReg_;
	ClientPtr									clientData_;
	std::queue<std::pair<Record, ObserverPtr>>	commandsWillBeDone_;
	std::vector<std::pair<Record, ObserverPtr>>	commandsHaveBeenDone_;
	Record										answerRecord_;
	Message										message_;
	std::vector<uint8_t>						data_;
//	string			ip_;
};

#endif // STACKOFMESSAGES_H
