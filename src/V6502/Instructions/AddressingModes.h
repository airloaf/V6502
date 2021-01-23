#pragma once

#include <V6502/MemoryBus.h>
#include <V6502/RegisterFile.h>

namespace V6502
{
    namespace AddressingModes
    {
        bool accumulator(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool immediate(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool absolute(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool zeroPage(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool zeroPageX(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool zeroPageY(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool indexedAbsoluteX(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool indexedAbsoluteY(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool implied(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool relative(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool indexedIndirect(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool indirectIndexed(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
        bool absoluteIndirect(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle);
    } // namespace AddressingModes
} // namespace V6502