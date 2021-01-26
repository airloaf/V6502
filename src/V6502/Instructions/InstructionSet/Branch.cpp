#include "Branch.h"

namespace V6502
{
    namespace InstructionSet
    {

        static struct Latch {
            bool boundaryCrossed;
        } latches;

        bool branch(RegisterFile &rf, bool condition, uint8_t offset, int cycle){
            if(!condition){
                return true;
            }else{
                if(cycle == 1){
                    int off = offset;
                    if((offset & 0x80) != 0){
                        off = -((offset ^ 0xFF) +1);
                    }
                    uint16_t pcAfter = rf.programCounter + off;
                    latches.boundaryCrossed = ((pcAfter & 0xFF00) != (rf.programCounter & 0xFF00));
                    rf.programCounter = pcAfter;
                }
                return (cycle == 1 && !latches.boundaryCrossed) || cycle == 2;
            }
        }

        bool BCC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return branch(rf, !rf.getCarry(), bus->read(decoded), cycle);
        }

        bool BCS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return branch(rf, rf.getCarry(), bus->read(decoded), cycle);
        }

        bool BEQ(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return branch(rf, rf.getZero(), bus->read(decoded), cycle);
        }

        bool BMI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return branch(rf, rf.getNegative(), bus->read(decoded), cycle);
        }

        bool BNE(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return branch(rf, !rf.getZero(), bus->read(decoded), cycle);
        }

        bool BPL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return branch(rf, !rf.getNegative(), bus->read(decoded), cycle);
        }

        bool BVC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return branch(rf, !rf.getOverflow(), bus->read(decoded), cycle);
        }

        bool BVS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return branch(rf, rf.getOverflow(), bus->read(decoded), cycle);
        }



        bool BRK(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool JMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool JSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool RTI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool RTS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

    } // namespace InstructionSet
} // namespace V6502