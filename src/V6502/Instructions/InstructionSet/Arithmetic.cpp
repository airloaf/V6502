#include "Arithmetic.h"

namespace V6502
{
    namespace InstructionSet
    {

        void setFlagsFromResult(RegisterFile &rf, uint8_t result){
            rf.setNegative((result & 0x80) != 0);
            rf.setZero(result == 0);
        }

        uint8_t twosComplementAddition(RegisterFile &rf, int lhs, int rhs){

            int op1 = lhs;
            int op2 = rhs;
            int carry = rf.getCarry()? 1: 0;
            int res = op1 + op2 + carry;
            if(res > 0xFF){
                rf.setCarry(true);
            }else{
                rf.setCarry(false);
            }

            uint8_t retValue = res;
            setFlagsFromResult(rf, retValue);
            rf.setOverflow((op1 & 0x80) == (op2 & 0x80) && (op1 & 0x80) != (res & 0x80));

            return retValue;

        }

        bool ADC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = twosComplementAddition(rf, rf.accumulator, bus->read(decoded));
            return true;
        }

        bool SBC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = twosComplementAddition(rf, rf.accumulator, (0xFF - bus->read(decoded)));
            return true;
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