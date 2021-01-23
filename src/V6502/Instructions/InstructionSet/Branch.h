#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        bool BCC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool BCS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool BEQ(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool BMI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool BNE(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool BPL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool BRK(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool BVC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool BVS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool JMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool JSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool RTI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool RTS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

    } // namespace InstructionSet
} // namespace V6502