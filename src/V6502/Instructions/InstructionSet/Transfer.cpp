#include "Transfer.h"

namespace V6502
{
    namespace InstructionSet
    {
        static void setStatusFromValue(RegisterFile &rf, uint8_t value)
        {
            rf.setZero(value == 0);
            rf.setNegative((value & 0x80) != 0);
        }

        // Transfer instructions
        bool TAX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = rf.accumulator;
            setStatusFromValue(rf, rf.indexX);
            return true;
        }

        bool TAY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY = rf.accumulator;
            setStatusFromValue(rf, rf.indexY);
            return true;
        }

        bool TSX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = rf.stackPointer;
            setStatusFromValue(rf, rf.indexX);
            return true;
        }

        bool TXA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = rf.indexX;
            setStatusFromValue(rf, rf.accumulator);
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
            setStatusFromValue(rf, rf.accumulator);
            return true;
        }

    } // namespace InstructionSet
} // namespace V6502