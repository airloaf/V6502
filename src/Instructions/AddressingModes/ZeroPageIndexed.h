#pragma once

#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

/**
 * @brief ZeroPageIndexed Addressing Mode
 *
 * This addressing mode will return the address directly after the program counter.
 * One cycle is needed to decode the address 
 */
class ZeroPageIndexed : public AddressingMode{
    public:
        /**
         * @brief Construct a new Zero Page Indexed Addressing Mode
         * 
         * @param useIndexX - Whether to use indexX or use indexY
         * true - use indexX
         * false - use indexY
         */
        ZeroPageIndexed(bool useIndexX);
        ~ZeroPageIndexed();

        void decodeTick(AddressBus *bus, RegisterFile &rf);
        uint16_t getDecodedAddress();
        bool isFinished();
        AddressingModeType getType();

    private:
        int mCycle; // Current cycle count
        uint16_t mReturnAddress; // The decoded address
        bool mUseIndexX;
};

}}