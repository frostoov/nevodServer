#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <iosfwd>
#include <string>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

class Value;

class JsonWriter
{
public:
	JsonWriter();
	~JsonWriter();

	const char* GetData();
	size_t GetSize();
	void StartDocument();
	void EndDocument();
	void StartRequest(const std::string& methodName, const Value& id);
	void EndRequest();
	void StartParameter();
	void EndParameter();
	void StartResponse(const Value& id);
	void EndResponse();
	void StartFaultResponse(const Value& id);
	void EndFaultResponse();
	void WriteFault(int32_t code, const std::string& string);
	void StartArray();
	void EndArray();
	void StartStruct();
	void EndStruct();
	void StartStructElement(const std::string& name);
	void EndStructElement();
	void WriteBinary(const char* data, size_t size);
	void WriteNull();
	void Write(bool value);
	void Write(double value);
	void Write(int32_t value);
	void Write(int64_t value);
	void Write(const std::string& value);
	void Write(const tm& value);

private:
	void WriteId(const Value& id);

	rapidjson::StringBuffer myStringBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> myWriter;
};

#endif
