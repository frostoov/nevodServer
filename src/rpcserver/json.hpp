#ifndef JSON_H
#define JSON_H

namespace xsonrpc {
namespace json {

const char JSONRPC_NAME[] = "jsonrpc";
const char JSONRPC_VERSION_2_0[] = "2.0";

const char METHOD_NAME[] = "method";
const char PARAMS_NAME[] = "params";
const char ID_NAME[] = "id";

const char RESULT_NAME[] = "result";

const char ERROR_NAME[] = "error";
const char ERROR_CODE_NAME[] = "code";
const char ERROR_MESSAGE_NAME[] = "message";

} // namespace json
} // namespace xsonrpc

#endif
