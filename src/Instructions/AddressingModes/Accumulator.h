#pragma once

#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

/**
 * @brief Accumulator Addressing Mode
 *
 * This addressing mode will return the address directly after the program counter.
 */
class Accumulator : public AddressingMode{
    public:
        Accumulator();
        ~Accumulator();

        void decodeTick(AddressBus *bus, RegisterFile &rf);
        uint16_t getDecodedAddress();
        bool isFinished();
        AddressingModeType getType();

    private:
        bool mDecoded; // Have we finished decoding
        uint16_t mReturnAddress; // The decoded address
};
}}