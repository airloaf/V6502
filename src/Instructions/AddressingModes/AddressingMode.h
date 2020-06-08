#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/AddressBus.h>
#include <stdint.h>

using namespace V6502;

/**
 * @brief The 13 different addressing modes for the 6502
 */
enum AddressingModeType {
    ACCUMULATOR,
    IMMEDIATE,
    ABSOLUTE,
    ZERO_PAGE,
    ZERO_PAGE_X,
    ZERO_PAGE_Y,
    INDEXED_ABSOLUTE_X,
    INDEXED_ABSOLUTE_Y,
    IMPLIED,
    RELATIVE,
    INDEXED_INDIRECT_X,
    INDEXED_INDIRECT_Y,
    ABSOLUTE_INDIRECT
};

/**
 * @brief Abstract class representing an addressing mode
 * 
 * Each addressing mode has different procedures for obtaining the memory address to retrieve values from
 */
class AddressingMode{
    public:
        AddressingMode();
        ~AddressingMode();

        /**
         * @brief Decodes the address using the given register file and address bus.
         * 
         * @param bus - The address bus to dereference memory.
         * @param rf  - The register file to get processor registers.
         * @return uint16_t 
         */
        virtual uint16_t decode(AddressBus *bus, RegisterFile &rf)=0;

        /**
         * @brief Determines if decoding the addressing mode has completed.
         * 
         * @return true 
         * @return false 
         */
        virtual bool isFinished()=0;

        /**
         * @brief Gets the type of addressing mode
         * 
         * @return AddressingModeType 
         */
        virtual AddressingModeType getType() = 0;
};