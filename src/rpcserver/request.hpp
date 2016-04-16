#ifndef XSONRPC_REQUEST_H
#define XSONRPC_REQUEST_H

#include "value.hpp"

#include <deque>
#include <string>

namespace xsonrpc {

class Writer;

class Request
{
public:
  typedef std::deque<Value> Parameters;

  Request(std::string methodName, Parameters parameters, Value id);

  const std::string& GetMethodName() const { return myMethodName; }
  const Parameters& GetParameters() const { return myParameters; }
  const Value& GetId() const { return myId; }

  void Write(Writer& writer) const;
  static void Write(const std::string& methodName, const Parameters& params,
                    const Value& id, Writer& writer);

private:
  std::string myMethodName;
  Parameters myParameters;
  Value myId;
};

} // namespace xsonrpc

#endif
