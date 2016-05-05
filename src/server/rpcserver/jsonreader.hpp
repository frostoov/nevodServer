#ifndef XSONRPC_JSONREADER_H
#define XSONRPC_JSONREADER_H

#include <string>

#include <json.hpp>

#include "request.hpp"
#include "response.hpp"
#include "value.hpp"

class JsonReader {
public:
	using Json = nlohmann::json;

	JsonReader(const std::string& data);
	~JsonReader();

	Request getRequest();
	Response getResponse();

private:
	void	validateJsonrpcVersion() const;
	Value	fromJsonToValue(const Json& json);

	std::string data_;
	Json		document_;
};

#endif
