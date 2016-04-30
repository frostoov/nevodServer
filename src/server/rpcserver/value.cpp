#include "value.hpp"

#include "fault.hpp"
#include "jsonwriter.hpp"

#include <limits>
#include <ostream>
#include <string>

Value::Value(Array value)
	: myType(Type::ARRAY)	{
	as.myArray = new Array(std::move(value));
}

Value::Value(const DateTime& value)
	: myType(Type::DATE_TIME)	{
	as.myDateTime = new DateTime(value);
	as.myDateTime->tm_isdst = -1;
}

Value::Value(int32_t value)
	: myType(Type::INTEGER_32)	{
	as.myInteger32 = value;
	as.myInteger64 = value;
	as.myDouble = value;
}

Value::Value(int64_t value)
	: myType(Type::INTEGER_64)	{
	as.myInteger32 = value;
	as.myInteger64 = value;
	as.myDouble = value;

	static_assert(std::numeric_limits<int64_t>::lowest()
				  >= std::numeric_limits<double>::lowest(), "");
	static_assert(std::numeric_limits<int64_t>::max()
				  <= std::numeric_limits<double>::max(), "");
}

Value::Value(String value, bool binary)
	: myType(binary ? Type::BINARY : Type::STRING)	{
	as.myString = new String(std::move(value));
}

Value::Value(Struct value)
	: myType(Type::STRUCT)	{
	as.myStruct = new Struct(std::move(value));
}

Value::~Value()	{
	Reset();
}

Value::Value(const Value& other)
	: myType(other.myType),
	  as(other.as)	{
	switch (myType) {
	case Type::BOOLEAN:
	case Type::DOUBLE:
	case Type::INTEGER_32:
	case Type::INTEGER_64:
	case Type::NIL:
		break;

	case Type::ARRAY:
		as.myArray = new Array(other.AsArray());
		break;
	case Type::DATE_TIME:
		as.myDateTime = new DateTime(other.AsDateTime());
		break;
	case Type::BINARY:
	case Type::STRING:
		as.myString = new String(other.AsString());
		break;
	case Type::STRUCT:
		as.myStruct = new Struct(other.AsStruct());
		break;
	}
}

Value::Value(Value&& other) noexcept
	: myType(other.myType),
	  as(other.as)	{
	other.myType = Type::NIL;
}

Value& Value::operator=(Value&& other) noexcept	{
	if (this != &other) {
		Reset();

		myType = other.myType;
		as = other.as;

		other.myType = Type::NIL;
	}
	return *this;
}

const Value::Array& Value::AsArray() const	{
	if (IsArray()) {
		return *as.myArray;
	}
	throw InvalidParametersFault();
}

const bool& Value::AsBoolean() const	{
	if (IsBoolean()) {
		return as.myBoolean;
	}
	throw InvalidParametersFault();
}

const Value::DateTime& Value::AsDateTime() const	{
	if (IsDateTime()) {
		return *as.myDateTime;
	}
	throw InvalidParametersFault();
}

const double& Value::AsDouble() const	{
	if (IsDouble() || IsInteger32() || IsInteger64()) {
		return as.myDouble;
	}
	throw InvalidParametersFault();
}

const int32_t& Value::AsInteger32() const	{
	if (IsInteger32()) {
		return as.myInteger32;
	}
	else if (IsInteger64()
			 && static_cast<int64_t>(as.myInteger32) == as.myInteger64) {
		return as.myInteger32;
	}
	throw InvalidParametersFault();
}

const int64_t& Value::AsInteger64() const	{
	if (IsInteger32() || IsInteger64()) {
		return as.myInteger64;
	}
	throw InvalidParametersFault();
}

const Value::String& Value::AsString() const	{
	if (IsString() || IsBinary()) {
		return *as.myString;
	}
	throw InvalidParametersFault();
}

const Value::Struct& Value::AsStruct() const	{
	if (IsStruct()) {
		return *as.myStruct;
	}
	throw InvalidParametersFault();
}

void Value::Write(JsonWriter& writer) const	{
	switch (myType) {
	case Type::ARRAY:
		writer.StartArray();
		for (auto& element : *as.myArray) {
			element.Write(writer);
		}
		writer.EndArray();
		break;
	case Type::BINARY:
		writer.WriteBinary(as.myString->data(), as.myString->size());
		break;
	case Type::BOOLEAN:
		writer.Write(as.myBoolean);
		break;
	case Type::DATE_TIME:
		writer.Write(*as.myDateTime);
		break;
	case Type::DOUBLE:
		writer.Write(as.myDouble);
		break;
	case Type::INTEGER_32:
		writer.Write(as.myInteger32);
		break;
	case Type::INTEGER_64:
		writer.Write(as.myInteger64);
		break;
	case Type::NIL:
		writer.WriteNull();
		break;
	case Type::STRING:
		writer.Write(*as.myString);
		break;
	case Type::STRUCT:
		writer.StartStruct();
		for (auto& element : *as.myStruct) {
			writer.StartStructElement(element.first);
			element.second.Write(writer);
			writer.EndStructElement();
		}
		writer.EndStruct();
		break;
	}
}

void Value::Reset()	{
	switch (myType) {
	case Type::ARRAY:
		delete as.myArray;
		break;
	case Type::DATE_TIME:
		delete as.myDateTime;
		break;
	case Type::BINARY:
	case Type::STRING:
		delete as.myString;
		break;
	case Type::STRUCT:
		delete as.myStruct;
		break;

	case Type::BOOLEAN:
	case Type::DOUBLE:
	case Type::INTEGER_32:
	case Type::INTEGER_64:
	case Type::NIL:
		break;
	}

	myType = Type::NIL;
}

std::ostream& operator<<(std::ostream& os, const Value& value)	{
	switch (value.GetType()) {
	case Value::Type::ARRAY: {
		os << '[';
		auto& a = value.AsArray();
		for (auto it = a.begin(); it != a.end(); ++it) {
			if (it != a.begin()) {
				os << ", ";
			}
			os << *it;
		}
		os << ']';
		break;
	}
		break;
	case Value::Type::BOOLEAN:
		os << value.AsBoolean();
		break;
		break;
	case Value::Type::DOUBLE:
		os << value.AsDouble();
		break;
	case Value::Type::INTEGER_32:
		os << value.AsInteger32();
		break;
	case Value::Type::INTEGER_64:
		os << value.AsInteger64();
		break;
	case Value::Type::NIL:
		os << "<nil>";
		break;
	case Value::Type::STRING:
		os << '"' << value.AsString() << '"';
		break;
	case Value::Type::STRUCT: {
		os << '{';
		auto& s = value.AsStruct();
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
