#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        bool DEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool DEX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool DEY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool INC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool INX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool INY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool LDA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool LDX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool LDY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool STA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool STX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool STY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    }; // namespace InstructionSet
} // namespace V6502