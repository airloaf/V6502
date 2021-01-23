#include "Memory.h"

namespace V6502
{
    namespace InstructionSet
    {
        void setStatusFromValue(RegisterFile &rf, uint8_t value)
        {
            rf.setZero(value == 0);
            rf.setNegative((value & 0x80) != 0);
        }

        void DEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t newValue = bus->read(decoded) - 1;
            bus->write(decoded, newValue);
            setStatusFromValue(rf, newValue);
        }

        void DEX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX--;
            setStatusFromValue(rf, rf.indexX);
        }

        void DEY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY--;
            setStatusFromValue(rf, rf.indexY);
        }

        void INC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t newValue = bus->read(decoded) + 1;
            bus->write(decoded, newValue);
            setStatusFromValue(rf, newValue);
        }

        void INX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX++;
            setStatusFromValue(rf, rf.indexX);
        }

        void INY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY++;
            setStatusFromValue(rf, rf.indexY);
        }

        void LDA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = bus->read(decoded);
            setStatusFromValue(rf, rf.accumulator);
        }

        void LDX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = bus->read(decoded);
            setStatusFromValue(rf, rf.indexX);
        }

        void LDY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY = bus->read(decoded);
            setStatusFromValue(rf, rf.indexY);
        }

        void STA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, rf.accumulator);
        }

        void STX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, rf.indexX);
        }

        void STY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, rf.indexY);
        }
    } // namespace InstructionSet
} // namespace V6502