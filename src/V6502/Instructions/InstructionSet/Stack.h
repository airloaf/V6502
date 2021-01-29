#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        bool PHA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool PHP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool PLA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool PLP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    } // namespace InstructionSet
} // namespace V6502