#include "stationconfig.hpp"

StationConfig::StationConfig() {}

StationConfig::~StationConfig() {}

bool StationConfig::readFromConfig(const std::string& configName) {
    try {
        std::ifstream file(configName);
        Json config;
        file >> config;
        file.close();
        configs_.clear();
        for (auto it = config.begin(); it != config.end(); ++it) {
            std::list<JsonPair> pairs = config[it.key()];
            configs_.insert(
                std::pair<std::string, std::list<JsonPair>>(it.key(), pairs));
        }
    } catch (std::exception& ex) {  // TODO
        return false;
    }
    return true;
}

bool StationConfig::writeToConfig(const std::string& configName) {
    try {
        Json config;
        for (auto& host : configs_)
            config[host.first] = Json(host.second);
        std::ofstream file(configName);
        file << config;
        file.close();
    } catch (std::exception& ex) {  // TODO
        return false;
    }
    return true;
}

bool StationConfig::addHost(const std::string& nameOfHost) {
    try {
        configs_.insert(std::pair<std::string, std::list<JsonPair>>(
            nameOfHost, std::list<JsonPair>()));
    } catch (std::exception& ex) {  // TODO
        return false;
    }
    return true;
}

bool StationConfig::addJsonPairToHost(const std::string& nameOfHost,
                                      const StationConfig::JsonPair& json) {
    try {
        configs_[nameOfHost].push_back(json);
    } catch (std::exception& ex) {
        return false;
    }
    return true;
}

bool StationConfig::deleteJsonPairFromHost(const std::string& nameOfHost,
                                           const std::string& nameOfMethod) {
    try {
        configs_[nameOfHost].remove_if([&nameOfMethod](JsonPair& pair) {
            return pair["method"] == nameOfMethod;
        });
    } catch (std::exception& ex) {
        return false;
    }
    return true;
}

bool StationConfig::deleteHost(const std::string& nameOfHost) {
    try {
        configs_.erase(nameOfHost);
    } catch (std::exception& ex) {
        return false;
    }
    return true;
}

std::list<StationConfig::Json> StationConfig::getReadyRpcJson(
    const std::string& nameOfHost) {
    return configs_[nameOfHost];
}

StationConfig::JsonPair StationConfig::rpcToPair(const Json& rpcJson) {
    JsonPair pairJson;
    pairJson["method"] = rpcJson["method"];
    pairJson["params"] = rpcJson["params"];
    return pairJson;
}

StationConfig::Json StationConfig::pairToRpc(const JsonPair& pairJson,
                                             int32_t id) {
    Json rpcJson(pairJson);
    rpcJson["jsonrpc"] = std::string("2.0");
    rpcJson["id"] = 0;
    return rpcJson;
}
