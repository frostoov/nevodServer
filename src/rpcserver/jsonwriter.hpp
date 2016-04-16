#ifndef JSONWRITER_H
#define JSONWRITER_H

#include "writer.hpp"

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace xsonrpc {

class JsonWriter final : public Writer
{
public:
  JsonWriter();

  // Writer
  const char* GetData() override;
  size_t GetSize() override;
  void StartDocument() override;
  void EndDocument() override;
  void StartRequest(const std::string& methodName, const Value& id) override;
  void EndRequest() override;
  void StartParameter() override;
  void EndParameter() override;
  void StartResponse(const Value& id) override;
  void EndResponse() override;
  void StartFaultResponse(const Value& id) override;
  void EndFaultResponse() override;
  void WriteFault(int32_t code, const std::string& string) override;
  void StartArray() override;
  void EndArray() override;
  void StartStruct() override;
  void EndStruct() override;
  void StartStructElement(const std::string& name) override;
  void EndStructElement() override;
  void WriteBinary(const char* data, size_t size) override;
  void WriteNull() override;
  void Write(bool value) override;
  void Write(double value) override;
  void Write(int32_t value) override;
  void Write(int64_t value) override;
  void Write(const std::string& value) override;
  void Write(const tm& value) override;

private:
  void WriteId(const Value& id);

  rapidjson::StringBuffer myStringBuffer;
  rapidjson::Writer<rapidjson::StringBuffer> myWriter;
};

} // namespace xsonrpc

#endif
