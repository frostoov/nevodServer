#ifndef RESPONSE_H
#define RESPONSE_H

#include "value.hpp"
#include "jsonwriter.hpp"

class Response
{
public:
	Response(Value value, Value id);
	Response(int32_t faultCode, std::string faultString, Value id);

	void Write(JsonWriter &writer) const;

	Value& GetResult() { return myResult; }
	bool IsFault() const { return myIsFault; }
	void ThrowIfFault() const;
	const Value& GetId() const { return myId; }

private:
	Value myResult;
	bool myIsFault;
	int32_t myFaultCode;
	std::string myFaultString;
	Value myId;
};

#endif
