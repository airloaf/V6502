#pragma once

#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

/**
 * @brief Immediate Addressing Mode
 *
 * This addressing mode will return the address directly after the program counter.
 * One cycle is needed to decode the address 
 */
class Immediate : public AddressingMode{
    public:
        Immediate();
        ~Immediate();

        void decodeTick(AddressBus *bus, RegisterFile &rf);
        uint16_t getDecodedAddress();
        bool isFinished();
        AddressingModeType getType();

    private:
        bool mDecoded; // Have we finished decoding
        uint16_t mReturnAddress; // The decoded address
};
}}