#include "jsonwriter.hpp"

#include "jsonconstants.hpp"
#include "value.hpp"

using namespace jsonconstants;

JsonWriter::JsonWriter()	{

}

JsonWriter::~JsonWriter()	{

}

void JsonWriter::setJson(const JsonWriter::Json &json)	{
	document = json;
}

//const char* JsonWriter::getData()	{
//	return document.dump().c_str();
//}

std::string JsonWriter::getData() const {
	return document.dump();
}

size_t JsonWriter::getSize()	{
	return document.size();
}

void JsonWriter::startDocument()	{
	// Empty
}

void JsonWriter::endDocument()	{
	// Empty
}

void JsonWriter::startRequest(const std::string& methodName, const Value& id)	{
	document[JSONRPC_NAME]	= JSONRPC_VERSION_2_0;
	document[METHOD_NAME]	= methodName;

	writeId(id);
	//TODO
}

void JsonWriter::endRequest()	{
}

void JsonWriter::startParameter()	{
	// Empty
}

void JsonWriter::endParameter()	{
	// Empty
}

void JsonWriter::startResponse(const Value& id)	{
	document[JSONRPC_NAME] = JSONRPC_VERSION_2_0;
	writeId(id);
}

void JsonWriter::endResponse()	{
}

void JsonWriter::startFaultResponse(const Value& id)	{
	document[JSONRPC_NAME] = JSONRPC_VERSION_2_0;

	writeId(id);
}

void JsonWriter::endFaultResponse()	{

}

void JsonWriter::writeFault(int32_t code, const std::string& string)	{
	document[ERROR_NAME] = {
		{ERROR_CODE_NAME, code},
		{ERROR_MESSAGE_NAME, string}
	};
}

void JsonWriter::startArray()	{
//	writer_.StartArray();
}

void JsonWriter::endArray()	{
//	writer_.EndArray();
}

void JsonWriter::startStruct()	{
//	writer_.StartObject();
}

void JsonWriter::endStruct()	{
//	writer_.EndObject();
}

void JsonWriter::startStructElement(const std::string& name)	{
//	writer_.Key(name.data(), name.size(), true);
}

void JsonWriter::endStructElement()	{
	// Empty
}

void JsonWriter::writeBinary(const char* data, size_t size)	{
//	writer_.String(data, size, true);
}

void JsonWriter::writeNull()	{
//	writer_.Null();
}

void JsonWriter::write(bool value)	{
//	writer_.Bool(value);
}

void JsonWriter::write(double value)	{
//	writer_.Double(value);
}

void JsonWriter::write(int32_t value)	{
//	writer_.Int(value);
}

void JsonWriter::write(int64_t value)	{
//	writer_.Int64(value);
}

void JsonWriter::write(const std::string& value)	{
//	writer_.String(value.data(), value.size(), true);
}

void JsonWriter::write(const tm& value)	{
//	Write(util::FormatIso8601DateTime(value));
}

void JsonWriter::writeId(const Value& id)	{
//	if (id.IsString() || id.IsInteger32() || id.IsInteger64() || id.IsNil()) {
//		writer_.Key(ID_NAME, sizeof(ID_NAME) - 1);
//		if (id.IsString()) {
//			writer_.String(id.AsString().data(), id.AsString().size(), true);
//		}
//		else if (id.IsInteger32()) {
//			writer_.Int(id.AsInteger32());
//		}
//		else if (id.IsInteger64()) {
//			writer_.Int64(id.AsInteger64());
//		}
//		else {
//			writer_.Null();
//		}
//	}
}
