#include <stdexcept>

#include "dispatcher.hpp"

MethodWrapper& MethodWrapper::setHelpText(std::string help)	{
	helpText_ = std::move(help);
	return *this;
}

std::vector<std::string> Dispatcher::getMethodNames(
		bool includeHidden) const	{
	std::vector<std::string> names;
	names.reserve(methods_.size());

	for (auto& method : methods_) {
		if (includeHidden || !method.second.isHidden()) {
			names.emplace_back(method.first);
		}
	}

	return names;
}

MethodWrapper& Dispatcher::getMethod(const std::string& name)	{
	return methods_.at(name);
}

MethodWrapper& Dispatcher::addMethod(
		std::string name, MethodWrapper::Method method)	{
	auto result = methods_.emplace(
				std::piecewise_construct,
				std::forward_as_tuple(std::move(name)),
				std::forward_as_tuple(std::move(method)));
	if (!result.second) {
		throw std::invalid_argument(name + ": method already added");
	}
	return result.first->second;
}

void Dispatcher::RemoveMethod(const std::string& name)	{
	methods_.erase(name);
}

Response Dispatcher::Invoke(const std::string& name,
							const Request::Parameters& parameters,
							const Value& id) const	{

	try {
		auto method = methods_.find(name);
		if (method == methods_.end()) {
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
