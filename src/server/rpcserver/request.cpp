#include "request.hpp"
#include "jsonwriter.hpp"
#include "jsonconstants.hpp"

using namespace jsonconstants;

Request::Request(std::string methodName, Parameters parameters, Value id)
	: methodName_(std::move(methodName)),
	  parameters_(std::move(parameters)),
	  id_(std::move(id))	{
	// Empty
}

void Request::write(JsonWriter &writer) const	{
	write(methodName_, parameters_, id_, writer);
}

void Request::write(const std::string& methodName, const Parameters& params,
					const Value& id, JsonWriter& writer)	{
//	writer.startDocument();
//	writer.startRequest(methodName, id);
//	for (auto& param : params) {
//		writer.startParameter();
//		param.write(writer);
//		writer.endParameter();
//	}
//	writer.endRequest();
//	writer.endDocument();

	Json json;
	json[JSONRPC_NAME]	= JSONRPC_VERSION_2_0;
	json[METHOD_NAME]	= methodName;
//	json[PARAMS_NAME]	= ;
	json[ID_NAME]		= id.asInteger32();
}
