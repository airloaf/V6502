#pragma once

#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

namespace V6502
{
    namespace InstructionSet
    {
        void ADC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void AND(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void ASL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BCC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BCS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BEQ(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BIT(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BMI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BNE(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BPL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BRK(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BVC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void BVS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CLC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CLD(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CLI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CLV(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CPX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void CPY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void DEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void DEX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void DEY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void EOR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void INC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void INX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void INY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void JMP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void JSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void LDA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void LDX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void LDY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void LSR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void NOP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void ORA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void PHA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void PHP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void PLA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void PLP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void ROL(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void ROR(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void RTI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void RTS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void SBC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void SEC(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void SED(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void SEI(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void STA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void STX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void STY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

        // Transfer instructions        
        void TAX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TAY(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TSX(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TXA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TXS(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
        void TYA(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);

    }; // namespace InstructionSet
} // namespace V6502