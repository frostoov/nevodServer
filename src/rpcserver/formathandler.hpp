#ifndef FORMATHANDLER_H
#define FORMATHANDLER_H

#include <memory>
#include <string>

namespace xsonrpc {

class Reader;
class Writer;

class FormatHandler
{
public:
  virtual ~FormatHandler() {}

  virtual bool CanHandleRequest(const std::string& path,
                                const std::string& contentType) = 0;
  virtual std::string GetContentType() = 0;
  virtual bool UsesId() = 0;
  virtual std::unique_ptr<Reader> CreateReader(std::string data) = 0;
  virtual std::unique_ptr<Writer> CreateWriter() = 0;
};

} // namespace xsonrpc

#endif
