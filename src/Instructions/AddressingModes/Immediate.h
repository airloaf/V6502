#pragma once

#include "AddressingMode.h"

/**
 * @brief Immediate Addressing Mode
 * 
 * This addressing mode will return the address directly after the given instruction.
 * Effectively this class will finish immediately and return the address right.
 */
class Immediate : public AddressingMode{
    public:
        Immediate();
        ~Immediate();

        uint16_t decode(AddressBus *bus, RegisterFile &rf);

        bool isFinished();
        AddressingModeType getType();

};