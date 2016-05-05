#include "response.hpp"

#include "fault.hpp"
#include "jsonwriter.hpp"
#include "jsonconstants.hpp"

using namespace jsonconstants;

Response::Response(Value value, Value id)
	: result_(std::move(value)),
	  isFault_(false),
	  faultCode_(0),
	  id_(std::move(id))	{
}

Response::Response(int32_t faultCode, std::string faultString, Value id)
	: isFault_(true),
	  faultCode_(faultCode),
	  faultString_(std::move(faultString)),
	  id_(std::move(id))	{
}

void Response::write(JsonWriter& writer) const	{
	Json json;
	json[JSONRPC_NAME]	= JSONRPC_VERSION_2_0;
	json[ID_NAME]		= id_.asInteger32();
	std::cout << json << std::endl;
	if (isFault_) {
		json[ERROR_NAME] = {
			{ERROR_CODE_NAME, faultCode_},
			{ERROR_MESSAGE_NAME, faultString_}
		};
	}
	else {
		json[RESULT_NAME] = fromValueToJson(result_);
		std::cout << json << std::endl;
	}
	std::cout << json << std::endl;
	writer.setJson(json);
}

void Response::throwIfFault() const	{
	if (!isFault()) {
		return;
	}

	switch (static_cast<Fault::ReservedCodes>(faultCode_)) {
	case Fault::RESERVED_CODE_MIN:
	case Fault::RESERVED_CODE_MAX:
	case Fault::SERVER_ERROR_CODE_MIN:
		break;
	case Fault::PARSE_ERROR:
		throw ParseErrorFault(faultString_);
	case Fault::INVALID_REQUEST:
		throw InvalidRequestFault(faultString_);
	case Fault::METHOD_NOT_FOUND:
		throw MethodNotFoundFault(faultString_);
	case Fault::INVALID_PARAMETERS:
		throw InvalidParametersFault(faultString_);
	case Fault::INTERNAL_ERROR:
		throw InternalErrorFault(faultString_);
	}

	if (faultCode_ >= Fault::SERVER_ERROR_CODE_MIN
			&& faultCode_ <= Fault::SERVER_ERROR_CODE_MAX) {
		throw ServerErrorFault(faultCode_, faultString_);
	}

	if (faultCode_ >= Fault::RESERVED_CODE_MIN
			&& faultCode_ <= Fault::RESERVED_CODE_MAX) {
		throw PreDefinedFault(faultCode_, faultString_);
	}

	throw Fault(faultString_, faultCode_);
}

Response::Json Response::fromValueToJson(const Value &value) const	{
	switch (value.getType()) {
//	  case Type::ARRAY:
//		writer.startArray();
//		for (auto& element : *as_.array) {
//		  element.write(writer);
//		}
//		writer.endArray();
//		break;
//	  case Type::BINARY:
//		writer.writeBinary(as_.string->data(), as_.string->size());
//		break;
	  case Value::Type::BOOLEAN:
		return Json(value.asBoolean());
//	  case Value::Type::DATE_TIME:
//		return Json(value.asDateTime())
	  case Value::Type::DOUBLE:
		return Json(value.asDouble());
	  case Value::Type::INTEGER_32:
		return Json(value.asInteger32());
	  case Value::Type::INTEGER_64:
		return Json(value.asInteger64());
	  case Value::Type::NIL:
		return Json(nullptr);
	  case Value::Type::STRING:
		return Json(value.asString());
//	  case Value::Type::STRUCT:
//		writer.startStruct();
//		for (auto& element : *as_.someStruct) {
//		  writer.startStructElement(element.first);
//		  element.second.write(writer);
//		  writer.endStructElement();
//		}
//		writer.endStruct();
//		break;
	}
}
