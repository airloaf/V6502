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
            case InstructionType::AND:
                AND(addressBus, rf);
            break;
            case InstructionType::ASL:
                ASL(addressBus, rf);
            break;
            case InstructionType::BCC:
                branchInstruction(addressBus, rf);
            break;
            case InstructionType::BCS:
                branchInstruction(addressBus, rf);
            break;
            case InstructionType::BEQ:
                branchInstruction(addressBus, rf);
            break;
            case InstructionType::BIT:
                BIT(addressBus, rf);
            break;
            case InstructionType::BMI:
                branchInstruction(addressBus, rf);
            break;
            case InstructionType::BNE:
                branchInstruction(addressBus, rf);
            break;
            case InstructionType::BPL:
                branchInstruction(addressBus, rf);
            break;
            case InstructionType::BRK:
                BRK(addressBus, rf);
            break;
            case InstructionType::BVC:
                branchInstruction(addressBus, rf);
            break;
            case InstructionType::BVS:
                branchInstruction(addressBus, rf);
            break;
            case InstructionType::CLC:
                CLC(addressBus, rf);
            break;
            case InstructionType::CLD:
                CLD(addressBus, rf);
            break;
            case InstructionType::CLI:
                CLI(addressBus, rf);
            break;
            case InstructionType::CLV:
                CLV(addressBus, rf);
            break;
            case InstructionType::CMP:
                CMP(addressBus, rf);
            break;
            case InstructionType::CPX:
                CPX(addressBus, rf);
            break;
            case InstructionType::CPY:
                CPY(addressBus, rf);
            break;
            case InstructionType::DEC:
                DEC(addressBus, rf);
            break;
            case InstructionType::DEX:
                DEX(addressBus, rf);
            break;
            case InstructionType::DEY:
                DEY(addressBus, rf);
            break;
            case InstructionType::EOR:
                EOR(addressBus, rf);
            break;
            case InstructionType::INC:
                INC(addressBus, rf);
            break;
            case InstructionType::INX:
                INX(addressBus, rf);
            break;
            case InstructionType::INY:
                INY(addressBus, rf);
            break;
            case InstructionType::JMP:
                JMP(addressBus, rf);
            break;
            case InstructionType::JSR:
                JSR(addressBus, rf);
            break;
            case InstructionType::LDA:
                LDA(addressBus, rf);
            break;
            case InstructionType::LDX:
                LDX(addressBus, rf);
            break;
            case InstructionType::LDY:
                LDY(addressBus, rf);
            break;
            case InstructionType::LSR:
                LSR(addressBus, rf);
            break;
            case InstructionType::NOP:
                NOP(addressBus, rf);
            break;
            case InstructionType::ORA:
                ORA(addressBus, rf);
            break;
            case InstructionType::PHA:
                PHA(addressBus, rf);
            break;
            case InstructionType::PHP:
                PHP(addressBus, rf);
            break;
            case InstructionType::PLA:
                PLA(addressBus, rf);
            break;
            case InstructionType::PLP:
                PLP(addressBus, rf);
            break;
            case InstructionType::ROL:
                ROL(addressBus, rf);
            break;
            case InstructionType::ROR:
                ROR(addressBus, rf);
            break;
            case InstructionType::RTI:
                RTI(addressBus, rf);
            break;
            case InstructionType::RTS:
                RTS(addressBus, rf);
            break;
            case InstructionType::SBC:
                SBC(addressBus, rf);
            break;
            case InstructionType::SEC:
                SEC(addressBus, rf);
            break;
            case InstructionType::SED:
                SED(addressBus, rf);
            break;
            case InstructionType::SEI:
                SEI(addressBus, rf);
            break;
            case InstructionType::STA:
                STA(addressBus, rf);
            break;
            case InstructionType::STX:
                STX(addressBus, rf);
            break;
            case InstructionType::STY:
                STY(addressBus, rf);
            break;
            case InstructionType::TAX:
                TAX(addressBus, rf);
            break;
            case InstructionType::TAY:
                TAY(addressBus, rf);
            break;
            case InstructionType::TSX:
                TSX(addressBus, rf);
            break;
            case InstructionType::TXA:
                TXA(addressBus, rf);
            break;
            case InstructionType::TXS:
                TXS(addressBus, rf);
            break;
            case InstructionType::TYA:
                TYA(addressBus, rf);
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

void Instruction::setStatusFlagsFromValue(uint8_t value, RegisterFile &rf){
        // Set the CPU flags
        rf.setZero(value == 0);
        rf.setNegative((value & 0x80) != 0);
}

void Instruction::branchInstruction(AddressBus *addressBus, RegisterFile &rf){
    // Check which cycle we are on
    if(mInstructionCycle == 0){
        // Check if we should branch
        bool branch = false;
        switch(mType){
            case InstructionType::BCC:
                branch = !rf.getCarry();
            break;
            case InstructionType::BCS:
                branch = rf.getCarry();
            break;
            case InstructionType::BEQ:
                branch = rf.getZero();
            break;
            case InstructionType::BMI:
                branch = rf.getNegative();
            break;
            case InstructionType::BNE:
                branch = !rf.getZero();
            break;
            case InstructionType::BPL:
                branch = !rf.getZero() and !rf.getNegative();
            break;
            case InstructionType::BVC:
                branch = !rf.getOverflow();
            break;
            case InstructionType::BVS:
                branch = rf.getOverflow();
            break;
        }

        // Get the relative branch address
        int8_t branchAddress = addressBus->read(mAddressingMode->getDecodedAddress());
        
        // Check if we should branch
        if(branch){
            // Branch occurs, increment base cycles by one
            mBaseCycles++;

            // Calculate the next program counter
            uint16_t nextProgramCounter = rf.programCounter + branchAddress;

            // Calculate the page before and after branching
            // Page number starts after the 8th bit of the address
            // Hence & with 0x10 to get the 9th bit. A branch
            // cannot move past two pages in a single operation
            // so we can simply check if the 9th bit of both
            // addresses equal each other.
            uint16_t pageAfter = nextProgramCounter & 0x10;
            uint16_t pageBefore = rf.programCounter & 0x10;

            // Check if branch to new page occurs
            if(pageBefore != pageAfter){
                // Increment base cycles by one again
                mBaseCycles++;
            }
            rf.programCounter += branchAddress;
        }
    }
    // increment the number of instruction cycles
    mInstructionCycle++;
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
        // If both the operand and the acccumulator have the same sign (8th bit) and the sum has a different sign, overflow occurs
        bool v = (((operand & 0x80) == (rf.accumulator & 0x80)) && ((operand & 0x80) != (sum & 0x80)));

        // Set the registers appropriately
        rf.accumulator = sum;
        rf.setCarry(c);
        rf.setOverflow(v);
        setStatusFlagsFromValue(sum, rf);
    }
    // increment the number of instruction cycles
    mInstructionCycle++;
}
void Instruction::AND(AddressBus *addressBus, RegisterFile &rf){
    // Check which cycle we are on
    if(mInstructionCycle == 0){

        // Get the operand value
        uint8_t operand = addressBus->read(mAddressingMode->getDecodedAddress());

        // And the operand with the accumulator
        rf.accumulator &= operand;

        // Set the CPU flags
        setStatusFlagsFromValue(rf.accumulator, rf);
    }
    // increment the number of instruction cycles
    mInstructionCycle++;
}
void Instruction::ASL(AddressBus *addressBus, RegisterFile &rf){
    // Check which cycle we are on
    if(mInstructionCycle == 0){

        uint8_t value = rf.accumulator;
        // Check what the addressing mode is
        if(mAddressingMode->getType() != ACCUMULATOR){
            // Get the operand value
            value = addressBus->read(mAddressingMode->getDecodedAddress());
        }


        // And the operand with the accumulator
        rf.accumulator = (value << 1);

        // Set the CPU flags
        setStatusFlagsFromValue(rf.accumulator, rf);
    }
    // increment the number of instruction cycles
    mInstructionCycle++;
}
void Instruction::BIT(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::BRK(AddressBus *addressBus, RegisterFile &rf){}
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
void Instruction::EOR(AddressBus *addressBus, RegisterFile &rf){
    // Check which cycle we are on
    if(mInstructionCycle == 0){

        // Get the operand value
        uint8_t operand = addressBus->read(mAddressingMode->getDecodedAddress());

        // And the operand with the accumulator
        rf.accumulator ^= operand;

        // Set the CPU flags
        setStatusFlagsFromValue(rf.accumulator, rf);
    }
    // increment the number of instruction cycles
    mInstructionCycle++;
}
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