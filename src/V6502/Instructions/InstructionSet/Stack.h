#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        void PHA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void PHP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void PLA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void PLP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    } // namespace InstructionSet
} // namespace V6502