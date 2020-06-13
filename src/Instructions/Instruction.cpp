#include "Instruction.h"

using namespace V6502::AddressingModes;

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
                arithmeticInstruction(addressBus, rf);
            break;
            case InstructionType::AND:
                arithmeticInstruction(addressBus, rf);
            break;
            case InstructionType::ASL:
                shiftInstruction(addressBus, rf);
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
                compareInstruction(addressBus, rf);
            break;
            case InstructionType::CPX:
                compareInstruction(addressBus, rf);
            break;
            case InstructionType::CPY:
                compareInstruction(addressBus, rf);
            break;
            case InstructionType::DEC:
                DEC(addressBus, rf);
            break;
            case InstructionType::DEX:
                registerInstruction(addressBus, rf);
            break;
            case InstructionType::DEY:
                registerInstruction(addressBus, rf);
            break;
            case InstructionType::EOR:
                arithmeticInstruction(addressBus, rf);
            break;
            case InstructionType::INC:
                INC(addressBus, rf);
            break;
            case InstructionType::INX:
                registerInstruction(addressBus, rf);
            break;
            case InstructionType::INY:
                registerInstruction(addressBus, rf);
            break;
            case InstructionType::JMP:
                JMP(addressBus, rf);
            break;
            case InstructionType::JSR:
                JSR(addressBus, rf);
            break;
            case InstructionType::LDA:
                loadInstruction(addressBus, rf);
            break;
            case InstructionType::LDX:
                loadInstruction(addressBus, rf);
            break;
            case InstructionType::LDY:
                loadInstruction(addressBus, rf);
            break;
            case InstructionType::LSR:
                shiftInstruction(addressBus, rf);
            break;
            case InstructionType::NOP:
                NOP(addressBus, rf);
            break;
            case InstructionType::ORA:
                arithmeticInstruction(addressBus, rf);
            break;
            case InstructionType::PHA:
                pushInstruction(addressBus, rf);
            break;
            case InstructionType::PHP:
                pushInstruction(addressBus, rf);
            break;
            case InstructionType::PLA:
                pullInstruction(addressBus, rf);
            break;
            case InstructionType::PLP:
                pullInstruction(addressBus, rf);
            break;
            case InstructionType::ROL:
                shiftInstruction(addressBus, rf);
            break;
            case InstructionType::ROR:
                shiftInstruction(addressBus, rf);
            break;
            case InstructionType::RTI:
                RTI(addressBus, rf);
            break;
            case InstructionType::RTS:
                RTS(addressBus, rf);
            break;
            case InstructionType::SBC:
                arithmeticInstruction(addressBus, rf);
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

void Instruction::arithmeticInstruction(AddressBus *addressBus, RegisterFile &rf){
    if(mInstructionCycle == 0){

        // Get the operand value
        uint8_t operand = addressBus->read(mAddressingMode->getDecodedAddress());

        // Get the accumulator before we change it. Used in overflow calculation
        uint8_t accumulatorBefore = rf.accumulator;

        // Result used for ADC and SBC
        int result;

        // Perform the operation
        switch(mType){
            case InstructionType::ADC:
                result = rf.accumulator + operand + (rf.getCarry()? 1: 0);
            break;
            case InstructionType::AND:
                result = rf.accumulator & operand;
            break;
            case InstructionType::EOR:
                result = rf.accumulator ^ operand;
            break;
            case InstructionType::ORA:
                result = rf.accumulator | operand;
            break;
            case InstructionType::SBC:
                result = rf.accumulator - operand + (rf.getCarry()? 0: 1);
            break;
        }

        // If the operation was adding or subtract, we need to set overflow and carry flag
        if(mType == InstructionType::ADC || mType == InstructionType::SBC){
            // If the sum cannot fit in an 8 bit value, carry is set to high
            bool c = (result > 0xFF);
            // If both the operand and the acccumulator have the same sign (8th bit) and the sum has a different sign, overflow occurs
            bool v = (((operand & 0x80) == (rf.accumulator & 0x80)) && ((operand & 0x80) != (result & 0x80)));

            // set carry and overflow
            rf.setCarry(c);
            rf.setOverflow(v);
        }

        // Set accumulator
        rf.accumulator = result;

        // Set the CPU flags
        setStatusFlagsFromValue(rf.accumulator, rf);

    }
    mInstructionCycle++;
}

void Instruction::shiftInstruction(AddressBus *addressBus, RegisterFile &rf){
    // Check which cycle we are on
    if(mInstructionCycle == 0){

        // Get the value for shifting
        uint8_t value = rf.accumulator;
        // Check what the addressing mode is
        if(mAddressingMode->getType() != ACCUMULATOR){
            // Get the operand value
            value = addressBus->read(mAddressingMode->getDecodedAddress());
        }

        // Get the carry bit
        bool carry;

        // perform the operation
        switch(mType){
            case InstructionType::ASL:
                carry = ((value & 0x80) != 0);
                value <<= 1;
            break;
            case InstructionType::LSR:
                carry = ((value & 0x01) != 0);
                value >>=1;
            break;
            case InstructionType::ROL:
                carry = ((value & 0x80) != 0);
                value <<= 1;
                if(carry){
                    value |= 0x01;
                }
            break;
            case InstructionType::ROR:
                carry = ((value & 0x01) != 0);
                value >>=1;
                if(carry){
                    value |= 0x80;
                }
            break;
        }

        // Check what the addressing mode is
        if(mAddressingMode->getType() != ACCUMULATOR){
            addressBus->write(mAddressingMode->getDecodedAddress(), value);
        }else{
            rf.accumulator = value;
        }

        // set the carry
        rf.setCarry(carry);

        // Set the CPU flags
        setStatusFlagsFromValue(rf.accumulator, rf);
    }
    // increment the number of instruction cycles
    mInstructionCycle++;
}

void Instruction::registerInstruction(AddressBus *addressBus, RegisterFile &rf){
    // Check which cycle we are on
    if(mInstructionCycle == 0){
        bool decrement = (mType == InstructionType::DEX || mType == InstructionType::DEY);
        bool xIndex = (mType == InstructionType::DEX || mType == InstructionType::INX);
        
        int value = rf.indexX;
        if(!xIndex){
            value = rf.indexY;
        }

        // Perform the operation
        if(decrement){
            value--;
        }else{
            value++;
        }

        // Check if we are using the x index
        if(xIndex){
            rf.indexX = value;
        }else{
            rf.indexY = value;
        }

        // Set the CPU flags
        setStatusFlagsFromValue(value, rf);
    }
    // increment the number of instruction cycles
    mInstructionCycle++;
}

void Instruction::loadInstruction(AddressBus *addressBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Get the decoded address
        uint16_t address = mAddressingMode->getDecodedAddress();

        // Get the value
        uint8_t value = addressBus->read(address);

        // Set the appropriate register
        switch(mType){
            case InstructionType::LDA:
                rf.accumulator = value;
            break;
            case InstructionType::LDX:
                rf.indexX = value;
            break;
            case InstructionType::LDY:
                rf.indexY = value;
            break;
        }

        // Set the CPU flags
        setStatusFlagsFromValue(value, rf);
    }
    mInstructionCycle++;
}

void Instruction::pushInstruction(AddressBus *addressBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Get the value
        uint8_t value = rf.accumulator;
        if(mType == InstructionType::PHP){
            value = rf.status;
        }

        // Store the value onto the stack
        addressBus->write(rf.stackPointer, value);

        // Move the stack down
        rf.stackPointer++;
    }
    mInstructionCycle++;
}
void Instruction::pullInstruction(AddressBus *addressBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Pull value from stack
        uint8_t value = addressBus->read(rf.stackPointer);

        // Store the value into a register
        if(mType == InstructionType::PLA){
            rf.accumulator = value;
        }else{
            rf.status = value;
        }

        // Move the stack up
        rf.stackPointer--;

        // Set cpu flags
        setStatusFlagsFromValue(value, rf);
    }
    mInstructionCycle++;
}

void Instruction::compareInstruction(AddressBus *addressBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        uint16_t decodedAddress = mAddressingMode->getDecodedAddress();

        // Get the value to compare with
        uint8_t compareValue = addressBus->read(decodedAddress);

        // Get the base value for comparison
        uint8_t baseValue = rf.accumulator;
        if(mType == InstructionType::CPX){
            baseValue = rf.indexX;
        }else if(mType == InstructionType::CPY){
            baseValue = rf.indexY;
        }

        // Subtract the two values
        uint8_t sub = baseValue - compareValue;

        // Calculate the carry flag value
        bool carry = false;
        if(baseValue > compareValue){
            carry = true;
        }

        // Set the carry flag
        rf.setCarry(carry);
        // Set CPU flags based off the subtracted value.
        setStatusFlagsFromValue(sub, rf);
    }
    mInstructionCycle++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// Instructions /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
void Instruction::INC(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::JMP(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::JSR(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::NOP(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::RTI(AddressBus *addressBus, RegisterFile &rf){}
void Instruction::RTS(AddressBus *addressBus, RegisterFile &rf){}
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