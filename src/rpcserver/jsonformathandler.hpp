#ifndef XSONRPC_JSONFORMATHANDLER_H
#define XSONRPC_JSONFORMATHANDLER_H

#include "formathandler.hpp"

namespace xsonrpc {

class JsonFormatHandler : public FormatHandler
{
public:
  explicit JsonFormatHandler(std::string requestPath = "/RPC2");

  // FormatHandler
  bool CanHandleRequest(const std::string& path,
                        const std::string& contentType) override;
  std::string GetContentType() override;
  bool UsesId() override;
  std::unique_ptr<Reader> CreateReader(std::string data) override;
  std::unique_ptr<Writer> CreateWriter() override;

private:
  std::string myRequestPath;
};

} // namespace xsonrpc

#endif
