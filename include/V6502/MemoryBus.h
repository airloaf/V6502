#pragma once

#include <stdint.h>

namespace V6502{

    /**
     * @brief Memory Bus Interface
     * 
     * Interface to be inherited for a memory bus. The memory bus must
     * provide two functions, read and write, which allow the CPU to commmunicate
     * with other devices connected to the bus (Memory, Cartridges, Controller, PPU).
     */
    class MemoryBus{

        public:
            /**
             * @brief Reads a byte from the given address
             * 
             * @param address - The address for the bus to read from
             * @return uint8_t - The byte read from memory
             */
            virtual uint8_t read(uint16_t address)=0;

            /**
             * @brief Writes a byte into memory
             * 
             * @param address - The address for the bus to write to
             * @param value - The byte to write into memory
             */
            virtual void write(uint16_t address, uint8_t value)=0;
    };

}