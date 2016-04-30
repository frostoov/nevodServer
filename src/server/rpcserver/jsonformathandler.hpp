#ifndef XSONRPC_JSONFORMATHANDLER_H
#define XSONRPC_JSONFORMATHANDLER_H

#include <memory>
#include <string>

#include "jsonreader.hpp"

class JsonFormatHandler	{
public:
	explicit JsonFormatHandler(std::string requestPath = "/RPC2");
	~JsonFormatHandler();

	// FormatHandler
	bool CanHandleRequest(const std::string& path,
						  const std::string& contentType);
	std::string GetContentType();
	bool UsesId();
	std::unique_ptr<JsonReader> CreateReader(std::string data);
	std::unique_ptr<JsonWriter> CreateWriter();

private:
	std::string myRequestPath;
};

#endif
