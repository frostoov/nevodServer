#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <iosfwd>
#include <string>

#include <json.hpp>

#include "value.hpp"

class JsonWriter	{
public:
	using json = nlohmann::json;

	JsonWriter();
	~JsonWriter();

	const char* getData();
	size_t getSize();
	void startDocument();
	void endDocument();
	void startRequest(const std::string& methodName, const Value& id);
	void endRequest();
	void startParameter();
	void endParameter();
	void startResponse(const Value& id);
	void endResponse();
	void startFaultResponse(const Value& id);
	void endFaultResponse();
	void writeFault(int32_t code, const std::string& string);
	void startArray();
	void endArray();
	void startStruct();
	void endStruct();
	void startStructElement(const std::string& name);
	void endStructElement();
	void writeBinary(const char* data, size_t size);
	void writeNull();
	void write(bool value);
	void write(double value);
	void write(int32_t value);
	void write(int64_t value);
	void write(const std::string& value);
	void write(const tm& value);

private:
	void writeId(const Value& id);

	json	document;
};

#endif
