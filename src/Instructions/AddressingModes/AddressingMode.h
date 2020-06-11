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
        /**
         * @brief Performs a single cycle in decoding the addressing mode
         * 
         * @param bus - The address bus to dereference memory.
         * @param rf  - The register file to get processor registers.
         */
        virtual void decodeTick(AddressBus *bus, RegisterFile &rf)=0;

        /**
         * @brief Get the Decoded Address for this addressing mode
         * 
         * You should only call this function after verifying the addressing mode has finished
         * 
         * @return uint16_t - The decoded address
         */
        virtual uint16_t getDecodedAddress()=0;

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