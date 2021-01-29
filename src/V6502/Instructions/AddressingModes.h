#pragma once

#include <V6502/MemoryBus.h>
#include <V6502/RegisterFile.h>

namespace V6502
{
    namespace AddressingModes
    {
        // 1 cycle
        // 1. Stall for cycle accuracy
        bool accumulator(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 1 cycle
        // 1. Fetch immediate
        bool immediate(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 3 cycles
        // 1. Fetch effective low
        // 2. Fetch effective high
        // 3. Stall for cycle accuracy
        bool absolute(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 2 cycles
        // 1. Fetch Zero Page Address
        // 2. Stall for cycle accuracy
        bool zeroPage(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 3 cycles
        // 1. Fetch Zero Page Address
        // 2. Add index (X/Y) to Zero Page Address (disregard high byte)
        // 3. Stall for cycle accuracy
        bool zeroPageX(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool zeroPageY(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 3* cycles
        // 1. Fetch effective low
        // 2. Fetch effective high and add index (X/Y)
        // 3*. Stall if a page boundary occured
        // 4. Stall for cycle accuracy
        bool indexedAbsoluteX(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool indexedAbsoluteY(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 1 cycle
        // 1. Stall for cycle accuracy
        bool implied(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 2 cycles
        // 1. Fetch target
        // 2. Stall for cycle accuracy
        bool relative(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 5 cycles
        // 1. Fetch target
        // 2. Add target to indexX, disregard high byte
        // 3. Fetch effective low
        // 4. Fetch effective high
        // 5. Stall for cycle accuracy
        bool indexedIndirect(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 4* cycles
        // 1. Fetch target
        // 2. Fetch effective Low
        // 3. Fetch effective high and add indexY
        // 4*. Stall if page boundary crossed
        // 5. Stall for cycle accuracy
        bool indirectIndexed(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

        // 5 cycles
        // 1. Fetch target low
        // 2. Fetch target high
        // 3. Fetch effective low
        // 4. Fetch effective high
        // 5. Stall for cycle accuracy
        bool absoluteIndirect(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);

    } // namespace AddressingModes
} // namespace V6502