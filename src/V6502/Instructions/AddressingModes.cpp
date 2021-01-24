#include "AddressingModes.h"

namespace V6502
{
    namespace AddressingModes
    {

        // Latches for storing data between cycles
        static bool boundaryCrossed = false;

        bool accumulator(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool immediate(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            decoded = rf.programCounter++;
            return true;
        }

        bool absolute(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            if(cycle == 0){
                decoded = bus->read(rf.programCounter++);
                decoded &= 0x00FF;
            }else if(cycle == 1){
                uint16_t highByte = (bus->read(rf.programCounter++) << 8);
                decoded |= highByte;
            }

            return cycle == 2;
        }

        bool zeroPage(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            if(cycle == 0){
                decoded = bus->read(rf.programCounter++);
                decoded &= 0x00FF;
            }

            return cycle == 1;
        }

        bool zeroPageX(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            if(cycle == 0){
                decoded = bus->read(rf.programCounter++);
            }else if(cycle == 1){
                decoded += rf.indexX;
                decoded &= 0x00FF;
            }

            return cycle == 2;
        }

        bool zeroPageY(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            if(cycle == 0){
                decoded = bus->read(rf.programCounter++);
            }else if(cycle == 1){
                decoded += rf.indexY;
                decoded &= 0x00FF;
            }

            return cycle == 2;
        }

        bool indexedAbsoluteX(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            if(cycle == 0){
                decoded = bus->read(rf.programCounter++);
                decoded &= 0x00FF;
            }else if(cycle == 1){
                decoded |= (bus->read(rf.programCounter++) << 8);
                uint16_t beforeAdd = decoded;
                decoded += rf.indexX;
                if((beforeAdd & 0xFF00) != (decoded & 0xFF00)){
                    boundaryCrossed = true;
                }else{
                    boundaryCrossed = false;
                }
            }

            return (cycle == 2 && !boundaryCrossed) || (cycle == 3);
        }

        bool indexedAbsoluteY(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            if(cycle == 0){
                decoded = bus->read(rf.programCounter++);
                decoded &= 0x00FF;
            }else if(cycle == 1){
                decoded |= (bus->read(rf.programCounter++) << 8);
                uint16_t beforeAdd = decoded;
                decoded += rf.indexY;
                if((beforeAdd & 0xFF00) != (decoded & 0xFF00)){
                    boundaryCrossed = true;
                }else{
                    boundaryCrossed = false;
                }
            }

            return (cycle == 2 && !boundaryCrossed) || (cycle == 3);
        }

        bool implied(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            return true;
        }

        bool relative(RegisterFile &rf, MemoryBus *bus, uint16_t &decoded, int cycle)
        {
            decoded = rf.programCounter++;
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