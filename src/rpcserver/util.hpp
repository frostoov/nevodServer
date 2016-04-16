#ifndef XSONRPC_UTIL_H
#define XSONRPC_UTIL_H

#include <stdint.h>
#include <string>

namespace tinyxml2 {
class XMLElement;
}

struct tm;

namespace xsonrpc {
namespace util {

bool IsTag(const tinyxml2::XMLElement& element, const char* tag);
bool HasEmptyText(const tinyxml2::XMLElement& element);

std::string FormatIso8601DateTime(const tm& dt);
bool ParseIso8601DateTime(const char* text, tm& dt);

inline std::string Base64Encode(const std::string& data);
std::string Base64Encode(const char* data, size_t size);

inline std::string Base64Decode(const std::string& str);
std::string Base64Decode(const char* str, size_t size);

} // namespace util
} // namespace xsonrpc

inline std::string xsonrpc::util::Base64Encode(const std::string& data)
{
  return Base64Encode(data.data(), data.size());
}

inline std::string xsonrpc::util::Base64Decode(const std::string& str)
{
  return Base64Decode(str.data(), str.size());
}

#endif
