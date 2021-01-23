#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        void DEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void DEX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void DEY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void INC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void INX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void INY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void LDA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void LDX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void LDY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void STA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void STX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void STY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    }; // namespace InstructionSet
} // namespace V6502