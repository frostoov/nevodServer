#ifndef XSONRPC_REQUEST_H
#define XSONRPC_REQUEST_H

#include <deque>
#include <string>
#include <json.hpp>

#include "jsonwriter.hpp"

class Request	{
public:
	using Json = nlohmann::json;
	using Parameters = std::deque<Value>;

	Request(std::string methodName, Parameters parameters, Value id);

	const std::string& getMethodName() const { return methodName_; }
	const Parameters& getParameters() const { return parameters_; }
	const Value& getId() const { return id_; }

	void write(JsonWriter& writer) const;
	static void write(const std::string& methodName, const Parameters& params,
					  const Value& id, JsonWriter &writer);

private:
	std::string methodName_;
	Parameters	parameters_;
	Value		id_;
};

#endif
