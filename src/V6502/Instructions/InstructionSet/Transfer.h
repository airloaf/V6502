#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        bool TAX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool TAY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool TSX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool TXA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool TXS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool TYA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    } // namespace InstructionSet
} // namespace V6502