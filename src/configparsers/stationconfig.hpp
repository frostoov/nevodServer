#ifndef STATIONCONFIG_HPP
#define STATIONCONFIG_HPP

#include <json.hpp>
#include <fstream>
#include <map>
#include <list>

#include "configrecord.hpp"

class StationConfig {
public:
    using Json = nlohmann::json;
    using JsonPair = nlohmann::json;

    StationConfig();
    ~StationConfig();

    bool readFromConfig(const std::string& configName);
    bool writeToConfig(const std::string& configName);
    bool addHost(const std::string& nameOfHost);
    bool addJsonPairToHost(const std::string& nameOfHost, const JsonPair& json);
    bool deleteJsonPairFromHost(const std::string& nameOfHost,
                                const std::string& nameOfMethod);
    bool deleteHost(const std::string& nameOfHost);
    std::list<Json> getReadyRpcJson(const std::string& nameOfHost);

protected:
    Json pairToRpc(const Json& rpcJson, int32_t id);
    JsonPair rpcToPair(const Json& pairJson);

private:
    std::map<std::string, std::list<JsonPair>> configs_;
};

#endif  // STATIONCONFIG_HPP
