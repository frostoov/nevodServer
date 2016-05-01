#include "response.hpp"

#include "fault.hpp"
#include "jsonwriter.hpp"

Response::Response(Value value, Value id)
	: myResult(std::move(value)),
	  myIsFault(false),
	  myFaultCode(0),
	  myId(std::move(id))	{
}

Response::Response(int32_t faultCode, std::string faultString, Value id)
	: myIsFault(true),
	  myFaultCode(faultCode),
	  myFaultString(std::move(faultString)),
	  myId(std::move(id))	{
}

void Response::Write(JsonWriter& writer) const	{
	writer.startDocument();
	if (myIsFault) {
		writer.startFaultResponse(myId);
		writer.writeFault(myFaultCode, myFaultString);
		writer.endFaultResponse();
	}
	else {
		writer.startResponse(myId);
		myResult.Write(writer);
		writer.endResponse();
	}
	writer.endDocument();
}

void Response::ThrowIfFault() const	{
	if (!IsFault()) {
		return;
	}

	switch (static_cast<Fault::ReservedCodes>(myFaultCode)) {
	case Fault::RESERVED_CODE_MIN:
	case Fault::RESERVED_CODE_MAX:
	case Fault::SERVER_ERROR_CODE_MIN:
		break;
	case Fault::PARSE_ERROR:
		throw ParseErrorFault(myFaultString);
	case Fault::INVALID_REQUEST:
		throw InvalidRequestFault(myFaultString);
	case Fault::METHOD_NOT_FOUND:
		throw MethodNotFoundFault(myFaultString);
	case Fault::INVALID_PARAMETERS:
		throw InvalidParametersFault(myFaultString);
	case Fault::INTERNAL_ERROR:
		throw InternalErrorFault(myFaultString);
	}

	if (myFaultCode >= Fault::SERVER_ERROR_CODE_MIN
			&& myFaultCode <= Fault::SERVER_ERROR_CODE_MAX) {
		throw ServerErrorFault(myFaultCode, myFaultString);
	}

	if (myFaultCode >= Fault::RESERVED_CODE_MIN
			&& myFaultCode <= Fault::RESERVED_CODE_MAX) {
		throw PreDefinedFault(myFaultCode, myFaultString);
	}

	throw Fault(myFaultString, myFaultCode);
}
