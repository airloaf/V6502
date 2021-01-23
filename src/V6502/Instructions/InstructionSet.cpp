#include "InstructionSet.h"
namespace V6502
{
    namespace InstructionSet
    {

        // MISC
        // void NOP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

        // Branch/Jump/Move instructions
        // void BCC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void BCS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void BEQ(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void BMI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void BNE(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void BPL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void BRK(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void BVC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void BVS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void JMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void JSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void RTI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void RTS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

        // Arithmetic instructions
        // void ADC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void AND(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void ASL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void EOR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void LSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void ORA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void ROL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void ROR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void SBC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

        // Status instructions
        // void BIT(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void CLC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void CLD(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void CLI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void CLV(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void CMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void CPX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void CPY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void SEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void SED(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void SEI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

        // Stack instructions
        // void PHA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void PHP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void PLA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        // void PLP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

        // Memory instructions
        void setStatusFromValue(RegisterFile &rf, uint8_t value)
        {
            rf.setZero(value == 0);
            rf.setNegative((value & 0x80) != 0);
        }

        void DEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t newValue = bus->read(decoded) - 1;
            bus->write(decoded, newValue);
            setStatusFromValue(rf, newValue);
        }

        void DEX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX--;
            setStatusFromValue(rf, rf.indexX);
        }

        void DEY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY--;
            setStatusFromValue(rf, rf.indexY);
        }

        void INC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            uint8_t newValue = bus->read(decoded) + 1;
            bus->write(decoded, newValue);
            setStatusFromValue(rf, newValue);
        }

        void INX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX++;
            setStatusFromValue(rf, rf.indexX);
        }

        void INY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY++;
            setStatusFromValue(rf, rf.indexY);
        }

        void LDA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = bus->read(decoded);
            setStatusFromValue(rf, rf.accumulator);
        }

        void LDX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = bus->read(decoded);
            setStatusFromValue(rf, rf.indexX);
        }

        void LDY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY = bus->read(decoded);
            setStatusFromValue(rf, rf.indexY);
        }

        void STA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, rf.accumulator);
        }

        void STX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, rf.indexX);
        }

        void STY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            bus->write(decoded, rf.indexY);
        }

        // Transfer instructions
        void TAX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = rf.accumulator;
        }

        void TAY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexY = rf.accumulator;
        }

        void TSX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.indexX = rf.stackPointer;
        }

        void TXA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = rf.indexX;
        }

        void TXS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.stackPointer = rf.indexX;
        }

        void TYA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle)
        {
            rf.accumulator = rf.indexY;
        }

    } // namespace InstructionSet
} // namespace V6502