#include "Status.h"

namespace V6502
{
    namespace InstructionSet
    {
        bool BIT(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t memValue = bus->read(decoded);
            rf.setNegative((memValue & 0x80) != 0);
            rf.setOverflow((memValue & 0x40) != 0);
            rf.setZero((memValue & rf.accumulator) == 0);
            return true;
        }

        bool CLC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setCarry(false);
            return true;
        }

        bool CLD(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setDecimalMode(false);
            return true;
        }

        bool CLI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setIRQDisable(false);
            return true;
        }

        bool CLV(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setOverflow(false);
            return true;
        }

        bool CMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t memValue = bus->read(decoded);
            rf.setZero(rf.accumulator == memValue);
            rf.setCarry(rf.accumulator >= memValue);
            uint8_t diff = rf.accumulator - memValue;
            rf.setNegative((diff & 0x80) != 0);
            return true;
        }

        bool CPX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t memValue = bus->read(decoded);
            rf.setZero(rf.indexX == memValue);
            rf.setCarry(rf.indexX >= memValue);
            uint8_t diff = rf.indexX - memValue;
            rf.setNegative((diff & 0x80) != 0);
            return true;
        }

        bool CPY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t memValue = bus->read(decoded);
            rf.setZero(rf.indexY == memValue);
            rf.setCarry(rf.indexY >= memValue);
            uint8_t diff = rf.indexY - memValue;
            rf.setNegative((diff & 0x80) != 0);
            return true;
        }

        bool SEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setCarry(true);
            return true;
        }

        bool SED(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setDecimalMode(true);
            return true;
        }

        bool SEI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setIRQDisable(true);
            return true;
        }

    } // namespace InstructionSet
} // namespace V6502