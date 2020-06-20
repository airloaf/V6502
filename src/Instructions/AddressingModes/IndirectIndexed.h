#pragma once

#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

/**
 * @brief IndirectIndexedAddressing Addressing Mode
 *
 * This addressing mode will return the address directly after the program counter.
 * One cycle is needed to decode the address 
 */
class IndirectIndexed: public AddressingMode{
    public:
        /**
         * @brief Construct a new Indexed Absolute Addressing Mode
         */
        IndirectIndexed();
        ~IndirectIndexed();

        void decodeTick(MemoryBus *bus, RegisterFile &rf);
        uint16_t getDecodedAddress();
        bool isFinished();
        AddressingModeType getType();
        bool hasCrossedPageBoundary();

    private:
        int mCycle; // Current cycle count
        uint16_t mReturnAddress; // The decoded address
        uint16_t mTargetAddress; // The address of the return address
        bool mPageBoundaryCrossed; // Have we crossed a page boundary
};

}}