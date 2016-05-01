#ifndef XSONRPC_JSONREADER_H
#define XSONRPC_JSONREADER_H

#include <string>

#include <json.hpp>

#include "request.hpp"
#include "response.hpp"
#include "value.hpp"

class JsonReader {
public:
	using json = nlohmann::json;

	JsonReader(const std::string& data);
	~JsonReader();

	Request getRequest();
	Response getResponse();
	Value getValue();

private:
	void validateJsonrpcVersion() const;

	std::string data_;
	json		document_;
};

#endif
