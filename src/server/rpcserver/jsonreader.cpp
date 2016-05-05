#include "jsonreader.hpp"

#include "fault.hpp"
#include "jsonconstants.hpp"
#include "request.hpp"
#include "response.hpp"

using namespace jsonconstants;

JsonReader::JsonReader(const std::string& data)	{
	document_ = json::parse(data);
	//TODO
}

JsonReader::~JsonReader()	{

}

Request JsonReader::getRequest()	{
	if (!document_.is_object())
		throw InvalidRequestFault();

	validateJsonrpcVersion();

	if (document_.find(METHOD_NAME) == document_.end())
		throw InvalidRequestFault();

	auto methodName = document_[METHOD_NAME];

	Request::Parameters parameters;
	if (document_.find(PARAMS_NAME) == document_.end())
		throw InvalidRequestFault();
	auto params_name = document_[PARAMS_NAME];

	if (!params_name.is_array())
		throw InvalidRequestFault();
	for (auto& param : params_name)
		parameters.emplace_back(param.dump());

	if (document_.find(ID_NAME) == document_.end())
		return Request(methodName.dump(), parameters, false);

	return Request(methodName.dump(), parameters, document_[ID_NAME]);
}

Response JsonReader::getResponse()	{
	if (!document_.is_object())
		throw InvalidRequestFault();

	validateJsonrpcVersion();

	if (document_.find(ID_NAME) == document_.end())
		throw InvalidRequestFault();

	auto result = document_.find(RESULT_NAME);
	auto error	= document_.find(ERROR_NAME);
	auto errorObj = document_[ERROR_NAME];

	if (result != document_.end()) {
		if (error != document_.end())
			throw InvalidRequestFault();

		return Response(document_[RESULT_NAME], document_[ID_NAME]);
	}
	else if (error != document_.end()) {
		if (result != document_.end()) {
			throw InvalidRequestFault();
		}
		if (!errorObj.is_object()) {
			throw InvalidRequestFault();
		}
		auto code = errorObj.find(ERROR_CODE_NAME);
		if (code == errorObj.end() || !errorObj[ERROR_CODE_NAME].is_number()) {
			throw InvalidRequestFault();
		}
		if (errorObj.find(ERROR_MESSAGE_NAME) == errorObj.end())
			throw InvalidRequestFault();
		if (!errorObj[ERROR_MESSAGE_NAME].is_string())
			throw InvalidRequestFault();

		return Response(errorObj[ERROR_CODE_NAME], errorObj[ERROR_MESSAGE_NAME].dump(), document_[ID_NAME]);
	}
	else {
		throw InvalidRequestFault();
	}
}

//Value JsonReader::getValue()	{
//	return getValue(myDocument);
//}

void JsonReader::validateJsonrpcVersion() const	{
	if (document_.find(JSONRPC_NAME) == document_.end())
		throw InvalidRequestFault();
	auto jsonrpc = document_[JSONRPC_NAME];
	if (!jsonrpc.is_string() || jsonrpc != JSONRPC_VERSION_2_0)
		throw InvalidRequestFault();
}
