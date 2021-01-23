#include "Transfer.h"

namespace V6502
{
    namespace InstructionSet
    {

        // Transfer instructions
        void TAX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = rf.accumulator;
        }

        void TAY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY = rf.accumulator;
        }

        void TSX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = rf.stackPointer;
        }

        void TXA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = rf.indexX;
        }

        void TXS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.stackPointer = rf.indexX;
        }

        void TYA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = rf.indexY;
        }

    } // namespace InstructionSet
} // namespace V6502