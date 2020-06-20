#pragma once

#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

/**
 * @brief ZeroPage Addressing Mode
 *
 * This addressing mode will return the address directly after the program counter.
 * One cycle is needed to decode the address 
 */
class ZeroPage : public AddressingMode{
    public:
        ZeroPage();
        ~ZeroPage();

        void decodeTick(MemoryBus *bus, RegisterFile &rf);
        uint16_t getDecodedAddress();
        bool isFinished();
        AddressingModeType getType();

    private:
        int mCycle; // The current cycle for the addressing mode
        uint16_t mReturnAddress; // The decoded address
};
}}