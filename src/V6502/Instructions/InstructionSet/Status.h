#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        bool BIT(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool CLC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool CLD(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool CLI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool CLV(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool CMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool CPX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool CPY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool SEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool SED(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool SEI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    } // namespace InstructionSet
} // namespace V6502