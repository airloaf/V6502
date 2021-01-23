#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        void ADC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void AND(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void ASL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void EOR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void LSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void ORA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void ROL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void ROR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void SBC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    } // namespace InstructionSet
} // namespace V6502