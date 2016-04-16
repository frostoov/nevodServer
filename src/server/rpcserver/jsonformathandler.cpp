#include "jsonformathandler.hpp"

#include "jsonreader.hpp"
#include "jsonwriter.hpp"

namespace {

const char APPLICATION_JSON[] = "application/json";

} // namespace

JsonFormatHandler::JsonFormatHandler(std::string requestPath)
	: myRequestPath(std::move(requestPath))
{
}

JsonFormatHandler::~JsonFormatHandler()
{

}

bool JsonFormatHandler::CanHandleRequest(
		const std::string& path, const std::string& contentType)
{
	return path == myRequestPath && contentType == APPLICATION_JSON;
}

std::string JsonFormatHandler::GetContentType()
{
	return APPLICATION_JSON;
}

bool JsonFormatHandler::UsesId()
{
	return true;
}

std::unique_ptr<JsonReader> JsonFormatHandler::CreateReader(std::string data)
{
	return std::unique_ptr<JsonReader>(new JsonReader(std::move(data)));
}

std::unique_ptr<JsonWriter> JsonFormatHandler::CreateWriter()
{
	return std::unique_ptr<JsonWriter>(new JsonWriter());
}
