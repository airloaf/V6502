#include "Stack.h"

namespace V6502
{
    namespace InstructionSet
    {
        void PHA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint16_t addr = (uint8_t) rf.stackPointer + 0x100;
            bus->write(addr, rf.accumulator);
            rf.stackPointer--;
        }

        void PHP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint16_t addr = (uint8_t) rf.stackPointer + 0x100;
            bus->write(addr, rf.status);
            rf.stackPointer--;
        }

        void PLA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.stackPointer++;
            uint16_t addr = (uint8_t) rf.stackPointer + 0x100;
            rf.accumulator = bus->read(addr);
        }

        void PLP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.stackPointer++;
            uint16_t addr = (uint8_t) rf.stackPointer + 0x100;
            rf.status = bus->read(addr);
        }

    } // namespace InstructionSet
} // namespace V6502