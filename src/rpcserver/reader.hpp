#ifndef READER_H
#define READER_H

namespace xsonrpc {

class Request;
class Response;
class Value;

class Reader
{
public:
  virtual ~Reader() {}

  virtual Request GetRequest() = 0;
  virtual Response GetResponse() = 0;
  virtual Value GetValue() = 0;
};

} // namespace xsonrpc

#endif
