#include "Status.h"

namespace V6502
{
    namespace InstructionSet
    {
        void BIT(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t memValue = bus->read(decoded);
            rf.setNegative((memValue & 0x80) != 0);
            rf.setOverflow((memValue & 0x40) != 0);
            rf.setZero((memValue & rf.accumulator) == 0);
        }

        void CLC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setCarry(false);
        }

        void CLD(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setDecimalMode(false);
        }

        void CLI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setIRQDisable(false);
        }

        void CLV(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setOverflow(false);
        }

        void CMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t memValue = bus->read(decoded);
            rf.setZero(rf.accumulator == memValue);
            rf.setCarry(rf.accumulator >= memValue);
            uint8_t diff = rf.accumulator - memValue;
            rf.setNegative((diff & 0x80) != 0);
        }

        void CPX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t memValue = bus->read(decoded);
            rf.setZero(rf.indexX == memValue);
            rf.setCarry(rf.indexX >= memValue);
            uint8_t diff = rf.indexX - memValue;
            rf.setNegative((diff & 0x80) != 0);
        }

        void CPY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t memValue = bus->read(decoded);
            rf.setZero(rf.indexY == memValue);
            rf.setCarry(rf.indexY >= memValue);
            uint8_t diff = rf.indexY - memValue;
            rf.setNegative((diff & 0x80) != 0);
        }

        void SEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setCarry(true);
        }

        void SED(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setDecimalMode(true);
        }

        void SEI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.setIRQDisable(true);
        }

    } // namespace InstructionSet
} // namespace V6502