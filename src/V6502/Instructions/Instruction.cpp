#include "Instruction.h"

using namespace V6502::AddressingModes;

Instruction::Instruction(AddressingMode *addressingMode, InstructionType type, int baseCycles): mAddressingMode{addressingMode}, mType{type}, mBaseCycles{baseCycles}, mCurrentCycle(0), mInstructionCycle(0){}

Instruction::~Instruction(){
    // Free up the addressing mode since we are no longer using it
    delete mAddressingMode;
}

void Instruction::tick(MemoryBus *memoryBus, RegisterFile &rf){
    // First we need to check if the addressing mode has completed decoding the address
    if(!mAddressingMode->isFinished()){
        mAddressingMode->decodeTick(memoryBus, rf);
    }else{
        switch(mType){
            case InstructionType::ADC:
                arithmeticInstruction(memoryBus, rf);
            break;
            case InstructionType::AND:
                arithmeticInstruction(memoryBus, rf);
            break;
            case InstructionType::ASL:
                shiftInstruction(memoryBus, rf);
            break;
            case InstructionType::BCC:
                branchInstruction(memoryBus, rf);
            break;
            case InstructionType::BCS:
                branchInstruction(memoryBus, rf);
            break;
            case InstructionType::BEQ:
                branchInstruction(memoryBus, rf);
            break;
            case InstructionType::BIT:
                BIT(memoryBus, rf);
            break;
            case InstructionType::BMI:
                branchInstruction(memoryBus, rf);
            break;
            case InstructionType::BNE:
                branchInstruction(memoryBus, rf);
            break;
            case InstructionType::BPL:
                branchInstruction(memoryBus, rf);
            break;
            case InstructionType::BRK:
                BRK(memoryBus, rf);
            break;
            case InstructionType::BVC:
                branchInstruction(memoryBus, rf);
            break;
            case InstructionType::BVS:
                branchInstruction(memoryBus, rf);
            break;
            case InstructionType::CLC:
                clearStatusInstructions(memoryBus, rf);
            break;
            case InstructionType::CLD:
                clearStatusInstructions(memoryBus, rf);
            break;
            case InstructionType::CLI:
                clearStatusInstructions(memoryBus, rf);
            break;
            case InstructionType::CLV:
                clearStatusInstructions(memoryBus, rf);
            break;
            case InstructionType::CMP:
                compareInstruction(memoryBus, rf);
            break;
            case InstructionType::CPX:
                compareInstruction(memoryBus, rf);
            break;
            case InstructionType::CPY:
                compareInstruction(memoryBus, rf);
            break;
            case InstructionType::DEC:
                memoryOperationInstructions(memoryBus, rf);
            break;
            case InstructionType::DEX:
                registerInstruction(memoryBus, rf);
            break;
            case InstructionType::DEY:
                registerInstruction(memoryBus, rf);
            break;
            case InstructionType::EOR:
                arithmeticInstruction(memoryBus, rf);
            break;
            case InstructionType::INC:
                memoryOperationInstructions(memoryBus, rf);
            break;
            case InstructionType::INX:
                registerInstruction(memoryBus, rf);
            break;
            case InstructionType::INY:
                registerInstruction(memoryBus, rf);
            break;
            case InstructionType::JMP:
                jumpInstructions(memoryBus, rf);
            break;
            case InstructionType::JSR:
                jumpInstructions(memoryBus, rf);
            break;
            case InstructionType::LDA:
                loadInstruction(memoryBus, rf);
            break;
            case InstructionType::LDX:
                loadInstruction(memoryBus, rf);
            break;
            case InstructionType::LDY:
                loadInstruction(memoryBus, rf);
            break;
            case InstructionType::LSR:
                shiftInstruction(memoryBus, rf);
            break;
            case InstructionType::NOP:
                NOP(memoryBus, rf);
            break;
            case InstructionType::ORA:
                arithmeticInstruction(memoryBus, rf);
            break;
            case InstructionType::PHA:
                pushInstruction(memoryBus, rf);
            break;
            case InstructionType::PHP:
                pushInstruction(memoryBus, rf);
            break;
            case InstructionType::PLA:
                pullInstruction(memoryBus, rf);
            break;
            case InstructionType::PLP:
                pullInstruction(memoryBus, rf);
            break;
            case InstructionType::ROL:
                shiftInstruction(memoryBus, rf);
            break;
            case InstructionType::ROR:
                shiftInstruction(memoryBus, rf);
            break;
            case InstructionType::RTI:
                returnInstructions(memoryBus, rf);
            break;
            case InstructionType::RTS:
                returnInstructions(memoryBus, rf);
            break;
            case InstructionType::SBC:
                arithmeticInstruction(memoryBus, rf);
            break;
            case InstructionType::SEC:
                setStatusInstructions(memoryBus, rf);
            break;
            case InstructionType::SED:
                setStatusInstructions(memoryBus, rf);
            break;
            case InstructionType::SEI:
                setStatusInstructions(memoryBus, rf);
            break;
            case InstructionType::STA:
                storeInstructions(memoryBus, rf);
            break;
            case InstructionType::STX:
                storeInstructions(memoryBus, rf);
            break;
            case InstructionType::STY:
                storeInstructions(memoryBus, rf);
            break;
            case InstructionType::TAX:
                transferInstructions(memoryBus, rf);
            break;
            case InstructionType::TAY:
                transferInstructions(memoryBus, rf);
            break;
            case InstructionType::TSX:
                transferInstructions(memoryBus, rf);
            break;
            case InstructionType::TXA:
                transferInstructions(memoryBus, rf);
            break;
            case InstructionType::TXS:
                transferInstructions(memoryBus, rf);
            break;
            case InstructionType::TYA:
                transferInstructions(memoryBus, rf);
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
    return mCurrentCycle >= (isDelayedByPageBoundary()? mBaseCycles + 1: mBaseCycles);
}

InstructionType Instruction::getType(){
    return mType;
}

void Instruction::setStatusFlagsFromValue(uint8_t value, RegisterFile &rf){
        // Set the CPU flags
        rf.setZero(value == 0);
        rf.setNegative((value & 0x80) != 0);
}

void Instruction::branchInstruction(MemoryBus *memoryBus, RegisterFile &rf){
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
                branch = !rf.getNegative();
            break;
            case InstructionType::BVC:
                branch = !rf.getOverflow();
            break;
            case InstructionType::BVS:
                branch = rf.getOverflow();
            break;
        }

        // Get the relative branch address
        int8_t branchAddress = memoryBus->read(mAddressingMode->getDecodedAddress());
        
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

void Instruction::arithmeticInstruction(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){

        // Get the operand value
        uint8_t operand = memoryBus->read(mAddressingMode->getDecodedAddress());

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
            // Check if the value will not fit inside a 16 bit value
            bool v = (result < -32768 || result > 32767);

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

void Instruction::shiftInstruction(MemoryBus *memoryBus, RegisterFile &rf){
    // Check which cycle we are on
    if(mInstructionCycle == 0){

        // Get the value for shifting
        uint8_t value = rf.accumulator;
        // Check what the addressing mode is
        if(mAddressingMode->getType() != ACCUMULATOR){
            // Get the operand value
            value = memoryBus->read(mAddressingMode->getDecodedAddress());
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
            memoryBus->write(mAddressingMode->getDecodedAddress(), value);
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

void Instruction::registerInstruction(MemoryBus *memoryBus, RegisterFile &rf){
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

void Instruction::loadInstruction(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Get the decoded address
        uint16_t address = mAddressingMode->getDecodedAddress();

        // Get the value
        uint8_t value = memoryBus->read(address);

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
void Instruction::storeInstructions(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Get the target location to store the value
        uint16_t targetAddress = mAddressingMode->getDecodedAddress();

        // Figure out which value to store into memory 
        uint8_t value = rf.accumulator;
        if(mType == InstructionType::STX){
            value = rf.indexX;
        }else if(mType == InstructionType::STY){
            value = rf.indexY;
        }

        // Store the value into memory
        memoryBus->write(targetAddress, value);
    }
    mInstructionCycle++;
}

void Instruction::pushInstruction(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Get the value
        uint8_t value = rf.accumulator;
        if(mType == InstructionType::PHP){
            rf.setBRKCommand(true);
            rf.status |= 0x20;
            value = rf.status;
        }

        // Store the value onto the stack
        memoryBus->write(0x0100 + rf.stackPointer, value);

        // Move the stack down
        rf.stackPointer--;
    }
    mInstructionCycle++;
}
void Instruction::pullInstruction(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Move the stack up
        rf.stackPointer++;

        // Pull value from stack
        uint8_t value = memoryBus->read(0x0100 + rf.stackPointer);

        // Store the value into a register
        if(mType == InstructionType::PLA){
            rf.accumulator = value;
        }else{
            rf.status = value;
        }

        // Set cpu flags if using the accumulator
        if(mType == InstructionType::PLA){
            setStatusFlagsFromValue(value, rf);
        }else{
            rf.status |= 0x20;
            rf.setBRKCommand(false);
        }
    }
    mInstructionCycle++;
}

void Instruction::compareInstruction(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        uint16_t decodedAddress = mAddressingMode->getDecodedAddress();

        // Get the value to compare with
        uint8_t compareValue = memoryBus->read(decodedAddress);

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
        // For some reason if the base value is >= to the compare value, carry is set.
        // One would think that if base value > compare value it would set the carry
        bool carry = false;
        if(baseValue >= compareValue){
            carry = true;
        }

        // Set the carry flag
        rf.setCarry(carry);
        // Set CPU flags based off the subtracted value.
        setStatusFlagsFromValue(sub, rf);
    }
    mInstructionCycle++;
}

void Instruction::setStatusInstructions(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        switch(mType){
            case InstructionType::SEC:
                rf.setCarry(true);
            break;
            case InstructionType::SED:
                rf.setDecimalMode(true);
            break;
            case InstructionType::SEI:
                rf.setIRQDisable(true);
            break;
        }
    }
    mInstructionCycle++;
}
void Instruction::clearStatusInstructions(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        switch(mType){
            case InstructionType::CLC:
                rf.setCarry(false);
            break;
            case InstructionType::CLD:
                rf.setDecimalMode(false);
            break;
            case InstructionType::CLI:
                rf.setIRQDisable(false);
            break;
            case InstructionType::CLV:
                rf.setOverflow(false);
            break;
        }
    }
    mInstructionCycle++;
}

void Instruction::transferInstructions(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){

        // The end value
        uint8_t value = rf.accumulator;
        if(mType == InstructionType::TSX){
            value = rf.stackPointer;
        }else if(mType == InstructionType::TXA || mType == InstructionType::TXS){
            value = rf.indexX;
        }else if(mType == InstructionType::TYA){
            value = rf.indexY;
        }

        // Set the appropriate register
        if(mType == InstructionType::TAX || mType == InstructionType::TSX){
            rf.indexX = value;
        }else if(mType == InstructionType::TAY){
            rf.indexY = value;
        }else if(mType == InstructionType::TXA || mType == InstructionType::TYA){
            rf.accumulator = value;
        }else{
            rf.stackPointer = value;
        }


        // Set the CPU flags
        setStatusFlagsFromValue(value, rf);
    }
    mInstructionCycle++;
}

void Instruction::jumpInstructions(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Get the target address
        uint16_t targetAddress = mAddressingMode->getDecodedAddress();

        // If the instruction is JSR, we need to store the return address onto the stack
        if(mType == InstructionType::JSR){
            uint16_t oldPC = rf.programCounter - 1;

            // Store the old program counter onto the stack
            memoryBus->write(0x100 + rf.stackPointer, ((oldPC & 0xFF00) >> 8));
            rf.stackPointer--;
            memoryBus->write(0x100 + rf.stackPointer, oldPC & 0xFF);
            rf.stackPointer--;
        }

        // Set the program counter
        rf.programCounter = targetAddress;
    }
    mInstructionCycle++;
}

void Instruction::memoryOperationInstructions(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Get the target value
        uint16_t targetAddress = mAddressingMode->getDecodedAddress();
        uint8_t value = memoryBus->read(targetAddress);

        if(mType == InstructionType::DEC){
            value--;
        }else if(mType == InstructionType::INC){
            value++;
        }

        // Write the modified value back into memory
        memoryBus->write(targetAddress, value);

        // Set the CPU flags from the modified value
        setStatusFlagsFromValue(value, rf);
    }
    mInstructionCycle++;
}

void Instruction::returnInstructions(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){

        uint8_t status = 0;
        // Check if we are returning from an interrupt
        if(mType == RTI){
            // Load the status register from the stack
            status = memoryBus->read((0x100) + (++rf.stackPointer));
        }

        // Load the program counter from the stack
        uint16_t programCounter = memoryBus->read((0x100) + (++rf.stackPointer));
        programCounter |= (memoryBus->read((0x100) + (++rf.stackPointer)) << 8);

        // If we are in an interrupt, set the status register
        if(mType == RTI){
            rf.status = status;
        }

        // Set the program counter
        rf.programCounter = programCounter;
    }
    mInstructionCycle++;
}

void Instruction::BIT(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Get the target value
        uint8_t value = memoryBus->read(mAddressingMode->getDecodedAddress());

        // And the two values
        uint8_t andValue = rf.accumulator & value;

        // Overflow is the 6th bit
        bool overflow = ((andValue & 0x40) != 0);
        rf.setOverflow(overflow);

        // Set the CPU Flags from the AND value
        setStatusFlagsFromValue(andValue, rf);
    }
    mInstructionCycle++;
}
void Instruction::BRK(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
        // Get the program counter and status register
        uint16_t pc = rf.programCounter;
        uint8_t status = rf.status;

        // Set the break status to true
        rf.setBRKCommand(true);
        status |= 0x20;

        // We need to push both of these items into the stack
        memoryBus->write(0x0100 + rf.stackPointer, (pc & 0x0F));
        rf.stackPointer--;
        memoryBus->write(0x0100 + rf.stackPointer, ((pc & 0xF0) >> 8));
        rf.stackPointer--;
        memoryBus->write(0x0100 + rf.stackPointer, status);
        rf.stackPointer--;

        // Read the next program counter at 0xFFFE/FFFF
        pc = 0;
        pc += memoryBus->read(0xFFFE);
        pc += (memoryBus->read(0xFFFF) << 8);
        
    }
    mInstructionCycle++;
}
void Instruction::NOP(MemoryBus *memoryBus, RegisterFile &rf){
    if(mInstructionCycle == 0){
    }
    mInstructionCycle++;
}

bool Instruction::isDelayedByPageBoundary(){
    // If we have not hit a page boundary return false by default
    if(!mAddressingMode->hasCrossedPageBoundary()){
        return false;
    }

    // Depending on the instruction type, we will be delayed
    InstructionType instructionType = mType;

    // Check which addressing mode is occuring
    if(mAddressingMode->getType() == INDEXED_ABSOLUTE_X || mAddressingMode->getType() == INDEXED_ABSOLUTE_Y){
        if(
            mType == InstructionType::ADC ||
            mType == InstructionType::AND ||
            mType == InstructionType::CMP ||
            mType == InstructionType::EOR ||
            mType == InstructionType::LDA ||
            mType == InstructionType::LDY ||
            mType == InstructionType::ORA ||
            mType == InstructionType::SBC
        ){
            // Instruction will delay
            return true;
        }
    }else if(mAddressingMode->getType() == INDIRECT_INDEXED){
        // Check if its not an STA instruction
        if(mType != InstructionType::STA){
            // Instruction will delay
            return true;
        }
    }
    return false;
}