#ifndef WRITER_H
#define WRITER_H

#include <string>

struct tm;

namespace xsonrpc {

class Value;

class Writer
{
public:
  virtual ~Writer() {}

  virtual const char* GetData() = 0;
  virtual size_t GetSize() = 0;

  virtual void StartDocument() = 0;
  virtual void EndDocument() = 0;

  virtual void StartRequest(const std::string& methodName,
                            const Value& id) = 0;
  virtual void EndRequest() = 0;
  virtual void StartParameter() = 0;
  virtual void EndParameter() = 0;

  virtual void StartResponse(const Value& id) = 0;
  virtual void EndResponse() = 0;
  virtual void StartFaultResponse(const Value& id) = 0;
  virtual void EndFaultResponse() = 0;
  virtual void WriteFault(int32_t code, const std::string& string) = 0;

  virtual void StartArray() = 0;
  virtual void EndArray() = 0;
  virtual void StartStruct() = 0;
  virtual void EndStruct() = 0;
  virtual void StartStructElement(const std::string& name) = 0;
  virtual void EndStructElement() = 0;
  virtual void WriteBinary(const char* data, size_t size) = 0;
  virtual void WriteNull() = 0;
  virtual void Write(bool value) = 0;
  virtual void Write(double value) = 0;
  virtual void Write(int32_t value) = 0;
  virtual void Write(int64_t value) = 0;
  virtual void Write(const std::string& value) = 0;
  virtual void Write(const tm& value) = 0;
};

} // namespace xsonrpc

#endif
