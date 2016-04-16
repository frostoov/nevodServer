#include "dispatcher.hpp"

#include <stdexcept>

namespace xsonrpc {

MethodWrapper& MethodWrapper::SetHelpText(std::string help)
{
  myHelpText = std::move(help);
  return *this;
}

std::vector<std::string> Dispatcher::GetMethodNames(
  bool includeHidden) const
{
  std::vector<std::string> names;
  names.reserve(myMethods.size());

  for (auto& method : myMethods) {
    if (includeHidden || !method.second.IsHidden()) {
      names.emplace_back(method.first);
    }
  }

  return names;
}

MethodWrapper& Dispatcher::GetMethod(const std::string& name)
{
  return myMethods.at(name);
}

MethodWrapper& Dispatcher::AddMethod(
  std::string name, MethodWrapper::Method method)
{
  auto result = myMethods.emplace(
    std::piecewise_construct,
    std::forward_as_tuple(std::move(name)),
    std::forward_as_tuple(std::move(method)));
  if (!result.second) {
    throw std::invalid_argument(name + ": method already added");
  }
  return result.first->second;
}

void Dispatcher::RemoveMethod(const std::string& name)
{
  myMethods.erase(name);
}

Response Dispatcher::Invoke(const std::string& name,
                            const Request::Parameters& parameters,
                            const Value& id) const
{
  try {
    auto method = myMethods.find(name);
    if (method == myMethods.end()) {
      throw MethodNotFoundFault("Method not found: " + name);
    }
    return {method->second(parameters), Value(id)};
  }
  catch (const Fault& fault) {
    return Response(fault.GetCode(), fault.GetString(), Value(id));
  }
  catch (const std::out_of_range&) {
    InvalidParametersFault fault;
    return Response(fault.GetCode(), fault.GetString(), Value(id));
  }
  catch (const std::exception& ex) {
    return Response(0, ex.what(), Value(id));
  }
  catch (...) {
    return Response(0, "unknown error", Value(id));
  }
}

} // namespace xsonrpc
