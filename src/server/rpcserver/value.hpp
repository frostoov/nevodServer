#ifndef VALUE_HPP
#define VALUE_HPP

#include <cstdint>
#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

struct tm;

class JsonWriter;

class Value {
public:
    using Array = std::vector<Value>;
    using DateTime = tm;
    using String = std::string;
    using Struct = std::map<std::string, Value>;

    enum class Type {
        ARRAY,
        BINARY,
        BOOLEAN,
        DATE_TIME,
        DOUBLE,
        INTEGER_32,
        INTEGER_64,
        NIL,
        STRING,
        STRUCT
    };

    Value() : type_(Type::NIL) {}
    Value(Array value);
    Value(bool value) : type_(Type::BOOLEAN) { as_.boolean = value; }
    Value(const DateTime& value);
    Value(double value) : type_(Type::DOUBLE) { as_.number = value; }
    Value(int32_t value);
    Value(int64_t value);
    Value(const char* value) : Value(String(value)) {}
    Value(String value, bool binary = false);
    Value(Struct value);

    template <typename T>
    Value(std::vector<T> value) : Value(Array{}) {
        as_.array->reserve(value.size());
        for (auto& v : value) {
            as_.array->emplace_back(std::move(v));
        }
    }

    template <typename T>
    Value(const std::map<std::string, T>& value) : Value(Struct{}) {
        for (auto& v : value) {
            as_.someStruct->emplace(v.first, v.second);
        }
    }

    template <typename T>
    Value(const std::unordered_map<std::string, T>& value) : Value(Struct{}) {
        for (auto& v : value) {
            as_.someStruct->emplace(v.first, v.second);
        }
    }

    ~Value();

    explicit Value(const Value&);
    Value& operator=(const Value&) = delete;
    Value(Value&& other) noexcept;
    Value& operator=(Value&& other) noexcept;

    bool isArray() const { return type_ == Type::ARRAY; }
    bool isBinary() const { return type_ == Type::BINARY; }
    bool isBoolean() const { return type_ == Type::BOOLEAN; }
    bool isDateTime() const { return type_ == Type::DATE_TIME; }
    bool isDouble() const { return type_ == Type::DOUBLE; }
    bool isInteger32() const { return type_ == Type::INTEGER_32; }
    bool isInteger64() const { return type_ == Type::INTEGER_64; }
    bool isNil() const { return type_ == Type::NIL; }
    bool isString() const { return type_ == Type::STRING; }
    bool isStruct() const { return type_ == Type::STRUCT; }

    const Array& asArray() const;
    const String& asBinary() const { return asString(); }
    const bool& asBoolean() const;
    const DateTime& asDateTime() const;
    const double& asDouble() const;
    const int32_t& asInteger32() const;
    const int64_t& asInteger64() const;
    const String& asString() const;
    const Struct& asStruct() const;

    template <typename T>
    inline const T& asType() const;

    Type getType() const { return type_; }

    void write(JsonWriter& writer) const;

    inline const Value& operator[](Array::size_type i) const;
    inline const Value& operator[](const Struct::key_type& key) const;

private:
    void reset();

    Type type_;
    union {
        Array* array;
        bool boolean;
        DateTime* dateTime;
        String* string;
        Struct* someStruct;
        struct {
            double number;
            int32_t integer32;
            int64_t integer64;
        };
    } as_;
};

template <>
inline const Value::Array& Value::asType<typename Value::Array>() const {
    return asArray();
}

template <>
inline const bool& Value::asType<bool>() const {
    return asBoolean();
}

template <>
inline const Value::DateTime& Value::asType<typename Value::DateTime>() const {
    return asDateTime();
}

template <>
inline const double& Value::asType<double>() const {
    return asDouble();
}

template <>
inline const int32_t& Value::asType<int32_t>() const {
    return asInteger32();
}

template <>
inline const int64_t& Value::asType<int64_t>() const {
    return asInteger64();
}

template <>
inline const Value::String& Value::asType<typename Value::String>() const {
    return asString();
}

template <>
inline const Value::Struct& Value::asType<typename Value::Struct>() const {
    return asStruct();
}

template <>
inline const Value& Value::asType<Value>() const {
    return *this;
}

inline const Value& Value::operator[](Array::size_type i) const {
    return asArray().at(i);
};

inline const Value& Value::operator[](const Struct::key_type& key) const {
    return asStruct().at(key);
}

std::ostream& operator<<(std::ostream& os, const Value& value);

#endif
