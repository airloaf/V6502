#include "AddressingModes.h"

namespace V6502
{
    namespace AddressingModes
    {
        bool accumulator(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool immediate(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool absolute(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool zeroPage(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool zeroPageX(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool zeroPageY(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool indexedAbsoluteX(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool indexedAbsoluteY(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool implied(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool relative(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool indexedIndirect(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool indirectIndexed(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool absoluteIndirect(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

    } // namespace AddressingModes
} // namespace V6502