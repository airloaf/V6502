#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        void BIT(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CLC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CLD(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CLI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CLV(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CPX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CPY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void SEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void SED(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void SEI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    } // namespace InstructionSet
} // namespace V6502