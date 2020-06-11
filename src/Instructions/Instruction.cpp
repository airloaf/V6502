#include "Instruction.h"

Instruction::Instruction(AddressingMode *addressingMode, InstructionType type, int baseCycles): mAddressingMode{addressingMode}, mType{type}, mBaseCycles{baseCycles}, mCurrentCycle(0), mInstructionCycle(0){}

Instruction::~Instruction(){
    // Free up the addressing mode since we are no longer using it
    delete mAddressingMode;
}

void Instruction::tick(AddressBus *addressBus, RegisterFile &rf){
    // First we need to check if the addressing mode has completed decoding the address
    if(!mAddressingMode->isFinished()){
        mAddressingMode->decodeTick(addressBus, rf);
    }else{
        switch(mType){
            case InstructionType::ADC:
                ADC(addressBus, rf);
            break;
            default:
            break;
        }
    }
    // Increment the number of cycles
    mCurrentCycle++;
}

bool Instruction::isFinished(){
    // The instruction is finished once the current cycle reaches or has exceeded the base number of cycles for this instruction.
    return (mCurrentCycle >= mBaseCycles);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// Instructions /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Instruction::ADC(AddressBus *addressBus, RegisterFile &rf){
    // Check which cycle we are on
    if(mInstructionCycle == 0){
        // Get the carry value
        int carry = rf.getCarry()? 1: 0;

        // Get the operand value
        uint8_t operand = addressBus->read(mAddressingMode->getDecodedAddress());

        // Calculate the sum
        int sum = rf.accumulator + operand + carry;

        // Calculate flags
        // If the sum cannot fit in an 8 bit value, carry is set to high
        bool c = (sum > 0xFF);
        // if the sum is zero, the zero flag is set to high
        bool z = (sum == 0);
        // If both the operand and the acccumulator have the same sign (8th bit) and the sum has a different sign, overflow occurs
        bool v = (((operand & 0x80) == (rf.accumulator & 0x80)) && ((operand & 0x80) != (sum & 0x80)));
        // If the 8th bit is high, the negative flag is high
        bool n = ((sum & 0x80) != 0);

        // Set the registers appropriately
        rf.accumulator = sum;
        rf.setCarry(c);
        rf.setZero(z);
        rf.setOverflow(v);
        rf.setNegative(n);
    }
    // increment the number of instruction cycles
    mInstructionCycle++;
}
void Instruction::AND(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::ASL(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BCC(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BCS(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BEQ(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BIT(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BMI(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BNE(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BPL(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BRK(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BVC(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BVS(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::CLC(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::CLD(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::CLI(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::CLV(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::CMP(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::CPX(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::CPY(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::DEC(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::DEX(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::DEY(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::EOR(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::INC(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::INX(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::INY(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::JMP(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::JSR(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::LDA(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::LDX(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::LDY(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::LSR(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::NOP(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::ORA(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::PHA(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::PHP(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::PLA(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::PLP(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::ROL(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::ROR(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::RTI(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::RTS(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::SBC(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::SEC(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::SED(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::SEI(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::STA(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::STX(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::STY(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::TAX(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::TAY(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::TSX(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::TXA(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::TXS(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::TYA(AddressBus *addressBus, RegisterFile &rf){}