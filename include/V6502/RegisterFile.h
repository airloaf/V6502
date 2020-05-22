#pragma once

#include <stdint.h>

namespace V6502 {
    /**
     * @brief Register File for the 6502 processor
     * 
     * The register file for the 6502 is accumulator based.
     * The registers indexX and indexY are used for calculating
     * offsets for some of the many addressing modes available to the 6502.
     * 
     * The program counter is 16 bit allowing the processor to acess up to 64 KB
     * of RAM.
     * The stack pointer is only 8 bit, although when it is used in reading or
     * writing to memory, it is extended to 16 bits, with the upper word being
     * set to the value of 1.
     */
    struct RegisterFile {
        uint16_t programCounter;
        uint8_t stackPointer;

        uint8_t accumulator;
        uint8_t indexX;
        uint8_t indexY;
        uint8_t status;

        // Helper functions to get and set bits in the status register
        bool getCarry();
        bool getZero();
        bool getIRQDisable();
        bool getDecimalMode();
        bool getBRKCommand();
        bool getOverflow();
        bool getNegative();
        
        void setCarry(bool set);
        void setZero(bool set);
        void setIRQDisable(bool set);
        void setDecimalMode(bool set);
        void setBRKCommand(bool set);
        void setOverflow(bool set);
        void setNegative(bool set);
    };
}