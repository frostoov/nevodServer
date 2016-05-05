#include <limits>
#include <ostream>
#include <string>

#include "value.hpp"
#include "fault.hpp"
#include "jsonwriter.hpp"

Value::Value(Array value)
  : type_(Type::ARRAY)	{
  as_.array = new Array(std::move(value));
}

Value::Value(const DateTime& value)
  : type_(Type::DATE_TIME)	{
  as_.dateTime = new DateTime(value);
  as_.dateTime->tm_isdst = -1;
}

Value::Value(int32_t value)
  : type_(Type::INTEGER_32)	{
  as_.integer32 = value;
  as_.integer64 = value;
  as_.number = value;
}

Value::Value(int64_t value)
  : type_(Type::INTEGER_64)	{
  as_.integer32 = value;
  as_.integer64 = value;
  as_.number = value;

  static_assert(std::numeric_limits<int64_t>::lowest()
                >= std::numeric_limits<double>::lowest(), "");
  static_assert(std::numeric_limits<int64_t>::max()
                <= std::numeric_limits<double>::max(), "");
}

Value::Value(String value, bool binary)
  : type_(binary ? Type::BINARY : Type::STRING)	{
  as_.string = new String(std::move(value));
}

Value::Value(Struct value)
  : type_(Type::STRUCT)	{
  as_.someStruct = new Struct(std::move(value));
}

Value::~Value()	{
  reset();
}

Value::Value(const Value& other)
  : type_(other.type_),
	as_(other.as_)	{
  switch (type_) {
    case Type::BOOLEAN:
    case Type::DOUBLE:
    case Type::INTEGER_32:
    case Type::INTEGER_64:
    case Type::NIL:
      break;

    case Type::ARRAY:
	  as_.array = new Array(other.asArray());
      break;
    case Type::DATE_TIME:
	  as_.dateTime = new DateTime(other.asDateTime());
      break;
    case Type::BINARY:
    case Type::STRING:
	  as_.string = new String(other.asString());
      break;
    case Type::STRUCT:
	  as_.someStruct = new Struct(other.asStruct());
      break;
  }
}

Value::Value(Value&& other) noexcept
  : type_(other.type_),
	as_(other.as_)	{
  other.type_ = Type::NIL;
}

Value& Value::operator=(Value&& other) noexcept	{
  if (this != &other) {
	reset();

	type_ = other.type_;
	as_ = other.as_;

	other.type_ = Type::NIL;
  }
  return *this;
}

const Value::Array& Value::asArray() const	{
  if (isArray()) {
	return *as_.array;
  }
  throw InvalidParametersFault();
}

const bool& Value::asBoolean() const	{
  if (isBoolean()) {
	return as_.boolean;
  }
  throw InvalidParametersFault();
}

const Value::DateTime& Value::asDateTime() const	{
  if (isDateTime()) {
	return *as_.dateTime;
  }
  throw InvalidParametersFault();
}

const double& Value::asDouble() const	{
  if (isDouble() || isInteger32() || isInteger64()) {
	return as_.number;
  }
  throw InvalidParametersFault();
}

const int32_t& Value::asInteger32() const	{
  if (isInteger32()) {
	return as_.integer32;
  }
  else if (isInteger64()
		   && static_cast<int64_t>(as_.integer32) == as_.integer64) {
	return as_.integer32;
  }
  throw InvalidParametersFault();
}

const int64_t& Value::asInteger64() const	{
  if (isInteger32() || isInteger64()) {
	return as_.integer64;
  }
  throw InvalidParametersFault();
}

const Value::String& Value::asString() const	{
  if (isString() || isBinary()) {
	return *as_.string;
  }
  throw InvalidParametersFault();
}

const Value::Struct& Value::asStruct() const	{
  if (isStruct()) {
	return *as_.someStruct;
  }
  throw InvalidParametersFault();
}

void Value::write(JsonWriter& writer) const	{
  switch (type_) {
    case Type::ARRAY:
	  writer.startArray();
	  for (auto& element : *as_.array) {
		element.write(writer);
      }
	  writer.endArray();
      break;
    case Type::BINARY:
	  writer.writeBinary(as_.string->data(), as_.string->size());
      break;
    case Type::BOOLEAN:
	  writer.write(as_.boolean);
      break;
    case Type::DATE_TIME:
	  writer.write(*as_.dateTime);
      break;
    case Type::DOUBLE:
	  writer.write(as_.number);
      break;
    case Type::INTEGER_32:
	  writer.write(as_.integer32);
      break;
    case Type::INTEGER_64:
	  writer.write(as_.integer64);
      break;
    case Type::NIL:
	  writer.writeNull();
      break;
    case Type::STRING:
	  writer.write(*as_.string);
      break;
    case Type::STRUCT:
	  writer.startStruct();
	  for (auto& element : *as_.someStruct) {
		writer.startStructElement(element.first);
		element.second.write(writer);
		writer.endStructElement();
      }
	  writer.endStruct();
      break;
  }
}

void Value::reset()	{
  switch (type_) {
    case Type::ARRAY:
	  delete as_.array;
      break;
    case Type::DATE_TIME:
	  delete as_.dateTime;
      break;
    case Type::BINARY:
    case Type::STRING:
	  delete as_.string;
      break;
    case Type::STRUCT:
	  delete as_.someStruct;
      break;

    case Type::BOOLEAN:
    case Type::DOUBLE:
    case Type::INTEGER_32:
    case Type::INTEGER_64:
    case Type::NIL:
      break;
  }

  type_ = Type::NIL;
}

std::ostream& operator<<(std::ostream& os, const Value& value)	{
  switch (value.getType()) {
    case Value::Type::ARRAY: {
      os << '[';
	  auto& a = value.asArray();
      for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) {
          os << ", ";
        }
        os << *it;
      }
      os << ']';
      break;
    }
    case Value::Type::BOOLEAN:
	  os << value.asBoolean();
      break;
    case Value::Type::DOUBLE:
	  os << value.asDouble();
      break;
    case Value::Type::INTEGER_32:
	  os << value.asInteger32();
      break;
    case Value::Type::INTEGER_64:
	  os << value.asInteger64();
      break;
    case Value::Type::NIL:
      os << "<nil>";
      break;
    case Value::Type::STRING:
	  os << '"' << value.asString() << '"';
      break;
    case Value::Type::STRUCT: {
      os << '{';
	  auto& s = value.asStruct();
      for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) {
          os << ", ";
        }
        os << it->first << ": " << it->second;
      }
      os << '}';
      break;
    }
  }
  return os;
}
