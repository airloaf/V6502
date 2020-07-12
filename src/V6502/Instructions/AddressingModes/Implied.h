#pragma once

#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

/**
 * @brief Implied Addressing Mode
 *
 * This addressing mode does not have a return address
 */
class Implied : public AddressingMode{
    public:
        Implied();
        ~Implied();

        void decodeTick(MemoryBus *bus, RegisterFile &rf);
        uint16_t getDecodedAddress();
        bool isFinished();
        AddressingModeType getType();

    private:
        bool mDecoded; // Have we finished decoding
};

}}