#include "Memory.h"

namespace V6502
{
    namespace InstructionSet
    {
        static void setStatusFromValue(RegisterFile &rf, uint8_t value)
        {
            rf.setZero(value == 0);
            rf.setNegative((value & 0x80) != 0);
        }

        bool DEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t newValue = bus->read(decoded) - 1;
            bus->write(decoded, newValue);
            setStatusFromValue(rf, newValue);
            return true;
        }

        bool DEX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX--;
            setStatusFromValue(rf, rf.indexX);
            return true;
        }

        bool DEY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY--;
            setStatusFromValue(rf, rf.indexY);
            return true;
        }

        bool INC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t newValue = bus->read(decoded) + 1;
            bus->write(decoded, newValue);
            setStatusFromValue(rf, newValue);
            return true;
        }

        bool INX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX++;
            setStatusFromValue(rf, rf.indexX);
            return true;
        }

        bool INY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY++;
            setStatusFromValue(rf, rf.indexY);
            return true;
        }

        bool LDA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = bus->read(decoded);
            setStatusFromValue(rf, rf.accumulator);
            return true;
        }

        bool LDX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = bus->read(decoded);
            setStatusFromValue(rf, rf.indexX);
            return true;
        }

        bool LDY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY = bus->read(decoded);
            setStatusFromValue(rf, rf.indexY);
            return true;
        }

        bool STA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, rf.accumulator);
            return true;
        }

        bool STX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, rf.indexX);
            return true;
        }

        bool STY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, rf.indexY);
            return true;
        }
    } // namespace InstructionSet
} // namespace V6502