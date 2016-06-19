#ifndef STATIONCONFIG_HPP
#define STATIONCONFIG_HPP

#include <json.hpp>

#include "configrecord.hpp"

class StationConfig {
public:
    using Json = nlohmann::json;

    StationConfig();
    ~StationConfig();

    bool readFromConfig(const std::string& configName);
    bool writeToConfig(const std::string& configName);

protected:

private:

};

#endif//STATIONCONFIG_HPP
