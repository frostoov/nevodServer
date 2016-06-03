#include "jsonreader.hpp"

#include "fault.hpp"
#include "jsonconstants.hpp"
#include "request.hpp"
#include "response.hpp"

using namespace jsonconstants;

JsonReader::JsonReader(const std::string& data) {
    document_ = Json::parse(data);
    // TODO
}

JsonReader::~JsonReader() {}

Value JsonReader::fromJsonToValue(const JsonReader::Json& json) {
    if (json.is_null())
        return Value(nullptr);
    if (json.is_number_integer())
        return Value(json.get<int32_t>());
    if (json.is_number_unsigned())
        return Value(json.get<int64_t>());  // TODO
    if (json.is_number_float())
        return Value(json.get<double>());
    if (json.is_string())
        return Value(json.get<std::string>());
    if (json.is_boolean())
        return Value(json.get<bool>());
}

Request JsonReader::getRequest() {
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
        parameters.emplace_back(fromJsonToValue(param));

    if (document_.find(ID_NAME) == document_.end())
        return Request(methodName.dump(), parameters, false);

    int id = document_[ID_NAME].get<int>();

    return Request(methodName.get<std::string>(), parameters, id);
}

Response JsonReader::getResponse() {
    if (!document_.is_object())
        throw InvalidRequestFault();

    validateJsonrpcVersion();

    if (document_.find(ID_NAME) == document_.end())
        throw InvalidRequestFault();

    auto result = document_.find(RESULT_NAME);
    auto error = document_.find(ERROR_NAME);
    auto errorObj = document_[ERROR_NAME];

    if (result != document_.end()) {
        if (error != document_.end())
            throw InvalidRequestFault();

        return Response(document_[RESULT_NAME], document_[ID_NAME]);
    } else if (error != document_.end()) {
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

        return Response(errorObj[ERROR_CODE_NAME],
                        errorObj[ERROR_MESSAGE_NAME].dump(),
                        document_[ID_NAME]);
    } else {
        throw InvalidRequestFault();
    }
}

void JsonReader::validateJsonrpcVersion() const {
    if (document_.find(JSONRPC_NAME) == document_.end())
        throw InvalidRequestFault();
    auto jsonrpc = document_[JSONRPC_NAME];
    if (!jsonrpc.is_string() || jsonrpc != JSONRPC_VERSION_2_0)
        throw InvalidRequestFault();
}
