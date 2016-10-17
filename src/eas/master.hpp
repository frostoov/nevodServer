#ifndef MASTER_HPP
#define MASTER_HPP

#include <cstdint>
#include <array>
#include <map>

#include "../observer/observer.hpp"
#include "../eas/adc.hpp"

class Master : public Observer, public Subject {
public:
    using AdcPtr = std::shared_ptr<Adc>;

    virtual AdcPtr addAdc(uint32_t numberAdc) = 0;

    virtual void writeHardReset() = 0;
    virtual void write200200() = 0;
    virtual void writeResolutionOfTimer(bool resolution) = 0;
    virtual void writeTestRegister(uint16_t data) = 0;
    virtual void writeCoincidence(uint32_t coincidence) = 0;
    virtual void writeResetCounter() = 0;
    virtual void writeTemporaryWindow(uint16_t window) = 0;
    virtual void writeMaskOfActiveChannels(
        const std::array<bool, 8>& activeChannels) = 0;
    virtual void writeChErrorCount(uint16_t data) = 0;
    virtual void writeControlTrigger(int i) = 0;
    virtual void writeProgramTrigger(bool trigger) = 0;
    virtual void writeResetVme() = 0;
    virtual void writeTime(uint16_t hours,
                           uint16_t minutes,
                           uint16_t seconds,
                           uint16_t ms) = 0;

    virtual std::map<uint32_t, AdcPtr>& getAdcs() = 0;

    virtual ~Master() {}
};

class MasterFactory {
public:
    using MasterPtr = std::shared_ptr<Master>;
    using QueuePtr = std::shared_ptr<QueueOfMessages>;

    virtual MasterPtr create(uint32_t offset, QueuePtr queue) = 0;

    virtual ~MasterFactory() {}
};

#endif//MASTER_HPP
