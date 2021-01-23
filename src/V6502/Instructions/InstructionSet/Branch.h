#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        void BCC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BCS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BEQ(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BMI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BNE(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BPL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BRK(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BVC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BVS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void JMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void JSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void RTI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void RTS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

    } // namespace InstructionSet
} // namespace V6502