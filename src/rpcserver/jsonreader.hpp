#ifndef XSONRPC_JSONREADER_H
#define XSONRPC_JSONREADER_H

#include "reader.hpp"

#include <rapidjson/document.h>
#include <string>

namespace xsonrpc {

class JsonReader final : public Reader
{
public:
  JsonReader(std::string data);

  // Reader
  Request GetRequest() override;
  Response GetResponse() override;
  Value GetValue() override;

private:
  void ValidateJsonrpcVersion() const;
  Value GetValue(const rapidjson::Value& value) const;
  Value GetId(const rapidjson::Value& id) const;

  std::string myData;
  rapidjson::Document myDocument;
};

} // namespace xsonrpc

#endif
