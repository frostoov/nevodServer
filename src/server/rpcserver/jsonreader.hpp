#ifndef XSONRPC_JSONREADER_H
#define XSONRPC_JSONREADER_H

#include <rapidjson/document.h>
#include <string>

#include "request.hpp"
#include "response.hpp"
#include "value.hpp"

class JsonReader
{
public:
	JsonReader(std::string data);
	~JsonReader();

	Request GetRequest();
	Response GetResponse();
	Value GetValue();

private:
	void ValidateJsonrpcVersion() const;
	Value GetValue(const rapidjson::Value& value) const;
	Value GetId(const rapidjson::Value& id) const;

	std::string myData;
	rapidjson::Document myDocument;
};

#endif
