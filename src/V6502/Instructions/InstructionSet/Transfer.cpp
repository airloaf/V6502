#include "Transfer.h"

namespace V6502
{
    namespace InstructionSet
    {

        // Transfer instructions
        bool TAX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = rf.accumulator;
            return true;
        }

        bool TAY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY = rf.accumulator;
            return true;
        }

        bool TSX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = rf.stackPointer;
            return true;
        }

        bool TXA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = rf.indexX;
            return true;
        }

        bool TXS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.stackPointer = rf.indexX;
            return true;
        }

        bool TYA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = rf.indexY;
            return true;
        }

    } // namespace InstructionSet
} // namespace V6502