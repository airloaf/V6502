#pragma once

#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

/**
 * @brief Absolute Indirect Addressing Mode
 *
 * This addressing mode will return the 16 bit address directly after the program
 * counter. This addressing mode takes 2 cycles to perform.
 */
class AbsoluteIndirect : public AddressingMode{
    public:
        AbsoluteIndirect();
        ~AbsoluteIndirect();

        void decodeTick(MemoryBus *bus, RegisterFile &rf);
        uint16_t getDecodedAddress();
        bool isFinished();
        AddressingModeType getType();

    private:
        int mCycle; // The current cycle for the addressing mode
        uint16_t mReturnAddress; // The decoded address
        uint16_t mIndirectAddress; // The address pointed by the two indirect bytes following the instruction byte
};
}}