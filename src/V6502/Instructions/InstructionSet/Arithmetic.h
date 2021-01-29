#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        bool ADC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool AND(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool ASL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool EOR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool LSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool ORA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool ROL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool ROR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool SBC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

        // Accumulator versions of the above
        bool ASL_ACCUM(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool LSR_ACCUM(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool ROL_ACCUM(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        bool ROR_ACCUM(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    } // namespace InstructionSet
} // namespace V6502