#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        // System Instructions
        bool BRK(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool JMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool JSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool NOP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool RTI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool RTS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    }; // namespace InstructionSet
} // namespace V6502