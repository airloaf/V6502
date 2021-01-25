#include "Arithmetic.h"

namespace V6502
{
    namespace InstructionSet
    {
        bool ADC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        bool SBC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            return true;
        }

        void setFlagsFromResult(RegisterFile &rf, uint8_t result){
            rf.setNegative((result & 0x80) != 0);
            rf.setZero(result == 0);
        }

        bool AND(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t res = rf.accumulator & bus->read(decoded);
            setFlagsFromResult(rf, res);
            rf.accumulator = res;
            return true;
        }

        bool EOR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t res = rf.accumulator ^ bus->read(decoded);
            setFlagsFromResult(rf, res);
            rf.accumulator = res;
            return true;
        }

        bool ORA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t res = rf.accumulator | bus->read(decoded);
            setFlagsFromResult(rf, res);
            rf.accumulator = res;
            return true;
        }

        uint8_t ASL(RegisterFile &rf, uint8_t value)
        {
            uint8_t retValue = value << 1;

            rf.setCarry((value & 0x80) != 0);
            setFlagsFromResult(rf, retValue);

            return retValue;
        }

        bool ASL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, ASL(rf, bus->read(decoded)));
            return true;
        }

        bool ASL_ACCUM(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = ASL(rf, rf.accumulator);
            return true;
        }

        uint8_t LSR(RegisterFile &rf, uint8_t value)
        {
            uint8_t retValue = value >> 1;

            rf.setCarry((value & 0x01) != 0);
            setFlagsFromResult(rf, retValue);

            return retValue;
        }

        bool LSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, LSR(rf, bus->read(decoded)));
            return true;
        }

        bool LSR_ACCUM(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = LSR(rf, rf.accumulator);
            return true;
        }

        uint8_t ROL(RegisterFile &rf, uint8_t value){
            uint8_t retValue = value << 1;
            if(rf.getCarry()){
                retValue |= 0x01;
            }

            rf.setCarry((value & 0x80) != 0);
            setFlagsFromResult(rf, retValue);

            return retValue;
        }

        bool ROL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, ROL(rf, bus->read(decoded)));
            return true;
        }

        bool ROL_ACCUM(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = ROL(rf, rf.accumulator);
            return true;
        }

        uint8_t ROR(RegisterFile &rf, uint8_t value){
            uint8_t retValue = value >> 1;
            if(rf.getCarry()){
                retValue |= 0x80;
            }

            rf.setCarry((value & 0x01) != 0);
            setFlagsFromResult(rf, retValue);

            return retValue;
        }

        bool ROR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, ROR(rf, bus->read(decoded)));
            return true;
        }

        bool ROR_ACCUM(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = ROR(rf, rf.accumulator);
            return true;
        }

    } // namespace InstructionSet
} // namespace V6502