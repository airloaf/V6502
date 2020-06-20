#pragma once

#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

/**
 * @brief IndexedIndirectAddressing Addressing Mode
 *
 * This addressing mode will return the address directly after the program counter.
 * One cycle is needed to decode the address 
 */
class IndexedIndirect: public AddressingMode{
    public:
        /**
         * @brief Construct a new Indexed Absolute Addressing Mode
         */
        IndexedIndirect();
        ~IndexedIndirect();

        void decodeTick(AddressBus *bus, RegisterFile &rf);
        uint16_t getDecodedAddress();
        bool isFinished();
        AddressingModeType getType();

    private:
        int mCycle; // Current cycle count
        uint16_t mReturnAddress; // The decoded address
        uint16_t mTargetAddress; // The address of the return address
};

}}