#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        void TAX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TAY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TSX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TXA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TXS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TYA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    } // namespace InstructionSet
} // namespace V6502