#ifndef EASSTATION_HPP
#define EASSTATION_HPP

#include <memory>
#include <boost/asio.hpp>

#include "host.hpp"
#include "realclient.hpp"
#include "realqueueofmessages.hpp"
//#include "client.hpp"
//#include "queueofmessages.hpp"

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

    bool writeBanOfTimestamps(int idHost, bool isBan);
    bool writeRegisterOfMasks(int idHost);
    bool writeHardReset(int idMaster);
    bool writePermissionOfMasters(int idMaster, int isOpen);
    bool writeControlDma(int idHost, int isOn);
    bool writeStartTaskMaster(int idMaster);
    bool writeRegisterOfReadData(int idHost,
                                 int isOnFirst,
                                 int isOnSecond,
                                 int isOnThird,
                                 int isOnFourth);
    bool writePermissionOfData(int idHost,
                               int isOnFirst,
                               int isOnSecond,
                               int isOnThird,
                               int isOnFourth);
    bool writeClearDataBuffer(int idHost);
    bool writeResetRegister(int idMaster);
    bool writePermissionOfTimer(int idMaster);
    bool writeSetCoincidence(int idMaster, int coincidence);
    bool writeResetCounter(int idMaster);
    bool writeSetTimeGate(int idMaster, int ns);
    bool writeActiveChannels(int idMaster,
                             int isOnFirst,
                             int isOnSecond,
                             int isOnThird,
                             int isOnFourth,
                             int isOnFifth,
                             int isOnSixth,
                             int isOnSeventh,
                             int isOnEighth);
    bool writeControlTrigger(int idMaster, int mode);
    bool writeProgramTrigger(int idMaster);
    bool writeResetVme(int idMaster);
    bool writeTime(int idMaster, int hours, int min, int sec, int ms);
    bool writeControlRegister(int idPaa);
    bool writeThreshold(int idPaa, int channel, int threshold);
    bool writeDelay(int idPaa, int channel, int delay);
    bool writeResetChannel(int idPaa, int channel);
    bool writeSmoothing(int idPaa, int smoothing);

    bool connectToHost(int idHost,
                       const std::string& ip,
                       int controlPort,
                       int dataPort);

    bool addMasterToHost(int idMaster);
    bool addAdcToMaster(int idPaa);
    bool setTaskTable(int idMaster);
    bool write200200(int idMaster);
    bool resolutionDataZero(int idHost);
    bool resolutionAndForbidOfData(int idHost, int resolution);

private:
    IoServicePtr service_;
    std::map<uint32_t, HostPtr> hosts_;
};

#endif  // EASSTATION_HPP
