
#include "System.h"

namespace V6502
{
    namespace InstructionSet
    {
        // System Instructions
        bool BRK(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool JMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool JSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool NOP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool RTI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool RTS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

    }; // namespace InstructionSet
} // namespace V6502