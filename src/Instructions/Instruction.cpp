#include "Instruction.h"

Instruction::Instruction(AddressingMode *addressingMode, InstructionType type, int baseCycles): mAddressingMode{addressingMode}, mType{type}, mBaseCycles{baseCycles}{}

Instruction::~Instruction(){
    // Free up the addressing mode since we are no longer using it
    delete mAddressingMode;
}

void Instruction::tick(){

}

bool Instruction::isFinished(){
    return false;
}