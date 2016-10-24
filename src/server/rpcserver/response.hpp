#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <json.hpp>
#include "jsonwriter.hpp"

class Response {
public:
    using Json = nlohmann::json;

    Response(Value value, Value id);
    Response(int32_t faultCode, std::string faultString, Value id);

    void write(JsonWriter& writer) const;

    Value& getResult() { return result_; }
    bool isFault() const { return isFault_; }
    void throwIfFault() const;
    const Value& getId() const { return id_; }

protected:
    Json fromValueToJson(const Value& value) const;

private:
    Value result_;
    bool isFault_;
    int32_t faultCode_;
    std::string faultString_;
    Value id_;
};

#endif//RESPONSE_HPP
