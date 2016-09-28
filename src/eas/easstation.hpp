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
    bool writeRegisterOfReadData(uint32_t idHost,
                                 bool isOnFirst,
                                 bool isOnSecond,
                                 bool isOnThird,
                                 bool isOnFourth);
    bool writePermissionOfData(uint32_t idHost,
                               bool isOnFirst,
                               bool isOnSecond,
                               bool isOnThird,
                               bool isOnFourth);
    bool writeClearDataBuffer(int idHost);
    bool writeResetRegister(int idMaster);
    bool writePermissionOfTimer(int idMaster);
    bool writeSetCoincidence(uint32_t idMaster, uint32_t coincidence);
    bool writeResetCounter(uint32_t idMaster);
    bool writeSetTimeGate(uint32_t idMaster, int ns);
    bool writeActiveChannels(uint32_t idMaster,
                             bool isOnFirst,
                             bool isOnSecond,
                             bool isOnThird,
                             bool isOnFourth,
                             bool isOnFifth,
                             bool isOnSixth,
                             bool isOnSeventh,
                             bool isOnEighth);
    bool writeControlTrigger(uint32_t idMaster, int mode);
    bool writeProgramTrigger(uint32_t idMaster);
    bool writeResetVme(uint32_t idMaster);
    bool writeTime(uint32_t idMaster, int hours, int min, int sec, int ms);
    bool writeControlRegister(uint32_t idPaa);
    bool writeThreshold(uint32_t idPaa, uint16_t threshold);
    bool writeDelay(uint32_t idPaa, uint32_t channel, uint16_t delay);
    bool writeResetChannel(uint32_t idPaa, uint32_t channel);
    bool writeSmoothing(uint32_t idPaa, uint16_t smoothing);

private:
    IoServicePtr service_;
    std::map<uint32_t, HostPtr> hosts_;
};

#endif  // EASSTATION_HPP
