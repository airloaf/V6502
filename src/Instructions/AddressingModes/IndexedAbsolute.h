#pragma once

#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

/**
 * @brief IndexedAbsolute Addressing Mode
 *
 * This addressing mode will return the address directly after the program counter.
 * One cycle is needed to decode the address 
 */
class IndexedAbsolute : public AddressingMode{
    public:
        /**
         * @brief Construct a new Indexed Absolute Addressing Mode
         * 
         * @param useIndexX - Whether to use indexX or use indexY
         * true - use indexX
         * false - use indexY
         */
        IndexedAbsolute(bool useIndexX);
        ~IndexedAbsolute();

        void decodeTick(AddressBus *bus, RegisterFile &rf);
        uint16_t getDecodedAddress();
        bool isFinished();
        AddressingModeType getType();
        bool hasCrossedPageBoundary();

    private:
        int mCycle; // Current cycle count
        uint16_t mReturnAddress; // The decoded address

        bool mUseIndexX;
        bool mPageBoundaryCrossed; // Have we crossed a page boundary
};

}}