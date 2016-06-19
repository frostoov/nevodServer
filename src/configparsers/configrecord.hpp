#ifndef CONFIGRECORD_HPP
#define CONFIGRECORD_HPP

#include <json.hpp>

class ConfigRecord {
public:
    using Json = nlohmann::json;

//    ConfigRecord();
//    ~ConfigRecord();

private:
    Json record_;
};

#endif//CONFIGRECORD_HPP
