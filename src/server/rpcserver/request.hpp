#ifndef XSONRPC_REQUEST_H
#define XSONRPC_REQUEST_H

#include <deque>
#include <string>

#include "jsonwriter.hpp"

class Request	{
public:
	typedef std::deque<Value> Parameters;

	Request(std::string methodName, Parameters parameters, Value id);

	const std::string& GetMethodName() const { return myMethodName; }
	const Parameters& GetParameters() const { return myParameters; }
	const Value& getId() const { return myId; }

	void Write(JsonWriter& writer) const;
	static void Write(const std::string& methodName, const Parameters& params,
					  const Value& id, JsonWriter &writer);

private:
	std::string myMethodName;
	Parameters myParameters;
	Value myId;
};

#endif
