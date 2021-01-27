#include "Stack.h"

namespace V6502
{
    namespace InstructionSet
    {
        bool PHA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint16_t addr = (uint8_t) rf.stackPointer + 0x100;
            bus->write(addr, rf.accumulator);
            rf.stackPointer--;
            return true;
        }

        bool PHP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint16_t addr = (uint8_t) rf.stackPointer + 0x100;
            bus->write(addr, rf.status);
            rf.stackPointer--;
            return true;
        }

        bool PLA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.stackPointer++;
            uint16_t addr = (uint8_t) rf.stackPointer + 0x100;
            rf.accumulator = bus->read(addr);
            return true;
        }

        bool PLP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.stackPointer++;
            uint16_t addr = (uint8_t) rf.stackPointer + 0x100;
            rf.status = bus->read(addr);
            rf.status |= 0x20;
            return true;
        }

    } // namespace InstructionSet
} // namespace V6502