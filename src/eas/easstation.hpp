#ifndef EASSTATION_HPP
#define EASSTATION_HPP

#include <memory>
#include <boost/asio.hpp>

#include "host.hpp"
#include "realclient.hpp"
#include "realqueueofmessages.hpp"

class EasStation {
public:
    using IoServicePtr = std::shared_ptr<boost::asio::io_service>;
    using HostPtr = std::shared_ptr<Host>;

    EasStation(const IoServicePtr& service);
    ~EasStation();

    HostPtr addHost(uint32_t numberHost,
                    const std::string& ip,
                    uint16_t registerPort,
                    uint16_t dataPort);
    void deleteHost(uint32_t numberHost);

    bool writeBanOfTimestamps(int32_t idHost, bool isBan);
    bool writeRegisterOfMasks(int idHost);
    bool writeHardReset(int idMaster);
    bool writePermissionOfMasters(int idMaster, bool isOpen);
    bool writeControlDma(int idHost, bool isOn);
    bool writeStartTaskMaster(int idMaster);
    bool writeRegisterOfReadData(int idHost);

private:
    IoServicePtr service_;
    std::map<uint32_t, HostPtr> hosts_;
};

#endif  // EASSTATION_HPP
