#ifndef JSON_H
#define JSON_H

#include <string>

namespace jsonconstants {

static const std::string JSONRPC_NAME = "jsonrpc";
static const std::string JSONRPC_VERSION_2_0 = "2.0";

static const std::string METHOD_NAME = "method";
static const std::string PARAMS_NAME = "params";
static const std::string ID_NAME = "id";
static const std::string RESULT_NAME = "result";

static const std::string ERROR_NAME = "error";
static const std::string ERROR_CODE_NAME = "code";
static const std::string ERROR_MESSAGE_NAME = "message";

} // namespace json

#endif
