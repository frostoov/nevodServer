#ifndef REALMASTER_HPP
#define REALMASTER_HPP

#include <cstdint>
#include <memory>
#include <vector>
#include <array>
#include <map>

#include "queueofmessages.hpp"
#include "adc.hpp"
#include "registers.hpp"
#include "master.hpp"

class RealMaster : public Master {
public:
	using QueuePtr = std::shared_ptr<QueueOfMessages>;
    using AdcPtr = std::shared_ptr<Adc>;

	RealMaster(uint32_t offset, QueuePtr clientQueue);
	~RealMaster();

	void update(const SubjectPtr subject);

    AdcPtr addAdc(uint32_t numberAdc);
    void deleteAdc(uint32_t numberAdc);
    void readState();

    void writeResetRegister();
    void writeResolutionOfTimer(bool resolution);
    void writeTestRegister(uint16_t data);
    void writeCoincidence(uint32_t coincidence);
    void writeResetCounter();
    void writeTemporaryWindow(uint16_t window);
    void writeMaskOfActiveChannels(const std::array<bool, 8>& activeChannels);
    void writeChErrorCount(uint16_t data);
    void writeControlTrigger(int i);
    void writeProgramTrigger(bool trigger);
    void writeResetVme();
    void writeTime(uint16_t hours,
                   uint16_t minutes,
                   uint16_t seconds,
                   uint16_t ms);

private:
    QueuePtr clientQueue_;
    std::vector<AdcPtr> adcs_;
    MasterRegisters registers_;
    uint32_t offset_;
    uint32_t offsetLink_;
};

#endif  // REALMASTER_HPP
