
#include "System.h"

namespace V6502
{
    namespace InstructionSet
    {

        void push(RegisterFile &rf, MemoryBus *bus, uint8_t value){
            uint16_t stackPtr = 0x100 | rf.stackPointer;
            rf.stackPointer--;
            bus->write(stackPtr, value);
        }

        uint8_t pop(RegisterFile &rf, MemoryBus *bus){
            rf.stackPointer++;
            uint16_t stackPtr = 0x100 | rf.stackPointer;
            return bus->read(stackPtr);
        }

        // System Instructions
        bool BRK(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            if(cycle == 0){
                rf.programCounter++;
                uint8_t high = ((rf.programCounter) & 0xFF00) >> 8;
                rf.status |= 0x10;
                push(rf, bus, high);
            }else if(cycle == 1){
                uint8_t low = ((rf.programCounter) & 0x00FF) >> 0;
                push(rf, bus, low);
            }else if(cycle == 2){
                push(rf, bus, rf.status);
            }else if(cycle == 3){
                rf.programCounter = bus->read(0xFFFE);
                rf.programCounter & 0x00FF;
            }else if(cycle == 4){
                rf.programCounter |= (bus->read(0xFFFF) << 8);
                rf.status |= 0x04;
            }
            return cycle == 4;
        }

        bool JMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.programCounter = decoded;
            return true;
        }

        bool JSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            if(cycle == 0){
                uint8_t high = ((rf.programCounter-1) & 0xFF00) >> 8;
                push(rf, bus, high);
            }else{
                uint8_t low = ((rf.programCounter-1) & 0x00FF) >> 0;
                push(rf, bus, low);
                rf.programCounter = decoded;
            }
            return cycle == 1;
        }

        bool NOP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool RTI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            if(cycle == 0){
                rf.status = pop(rf, bus);
            }else if(cycle == 1){
                rf.programCounter = pop(rf, bus);
                rf.programCounter &= 0x00FF;
            }else if(cycle == 2){
                rf.programCounter |= (pop(rf, bus) << 8);
            }
            return cycle == 3;
        }

        bool RTS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            if(cycle == 0){
                rf.programCounter = pop(rf, bus);
                rf.programCounter &= 0x00FF;
            }else if(cycle == 1){
                rf.programCounter |= (pop(rf, bus) << 8);
            }else if(cycle == 2){
                rf.programCounter++;
            }
            return cycle == 3;
        }

    }; // namespace InstructionSet
} // namespace V6502