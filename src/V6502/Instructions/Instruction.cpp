#include "Instruction.h"

#include <functional>
#include "AddressingModes.h"
#include "InstructionSet/InstructionSet.h"

using namespace V6502;

typedef std::function<bool(RegisterFile &, MemoryBus *, uint16_t &, int)> AddressingModeOperation;
typedef std::function<bool(RegisterFile &, MemoryBus *, uint16_t, int)> InstructionSetOperation;

static const AddressingModeOperation addressingModeOperations[] = {
    AddressingModes::accumulator,
    AddressingModes::immediate,
    AddressingModes::absolute,
    AddressingModes::zeroPage,
    AddressingModes::zeroPageX,
    AddressingModes::zeroPageY,
    AddressingModes::indexedAbsoluteX,
    AddressingModes::indexedAbsoluteY,
    AddressingModes::implied,
    AddressingModes::relative,
    AddressingModes::indexedIndirect,
    AddressingModes::indirectIndexed,
    AddressingModes::absoluteIndirect};

static const InstructionSetOperation instructionSetOperations[] = {
    InstructionSet::ADC,
    InstructionSet::AND,
    InstructionSet::ASL,
    InstructionSet::BCC,
    InstructionSet::BCS,
    InstructionSet::BEQ,
    InstructionSet::BIT,
    InstructionSet::BMI,
    InstructionSet::BNE,
    InstructionSet::BPL,
    InstructionSet::BRK,
    InstructionSet::BVC,
    InstructionSet::BVS,
    InstructionSet::CLC,
    InstructionSet::CLD,
    InstructionSet::CLI,
    InstructionSet::CLV,
    InstructionSet::CMP,
    InstructionSet::CPX,
    InstructionSet::CPY,
    InstructionSet::DEC,
    InstructionSet::DEX,
    InstructionSet::DEY,
    InstructionSet::EOR,
    InstructionSet::INC,
    InstructionSet::INX,
    InstructionSet::INY,
    InstructionSet::JMP,
    InstructionSet::JSR,
    InstructionSet::LDA,
    InstructionSet::LDX,
    InstructionSet::LDY,
    InstructionSet::LSR,
    InstructionSet::NOP,
    InstructionSet::ORA,
    InstructionSet::PHA,
    InstructionSet::PHP,
    InstructionSet::PLA,
    InstructionSet::PLP,
    InstructionSet::ROL,
    InstructionSet::ROR,
    InstructionSet::RTI,
    InstructionSet::RTS,
    InstructionSet::SBC,
    InstructionSet::SEC,
    InstructionSet::SED,
    InstructionSet::SEI,
    InstructionSet::STA,
    InstructionSet::STX,
    InstructionSet::STY,
    InstructionSet::TAX,
    InstructionSet::TAY,
    InstructionSet::TSX,
    InstructionSet::TXA,
    InstructionSet::TXS,
    InstructionSet::TYA
};

Instruction::Instruction() : mCurrentCycle(0), mInstructionCycle(0), mAddressingCycle(0), mFinished(true), mAddressingFinished(false)
{
}

Instruction::~Instruction() {}

void Instruction::init(InstructionMetaInfo instructionInfo)
{
    mInfo = instructionInfo;

    mCurrentCycle = 0;
    mInstructionCycle = 0;
    mAddressingCycle = 0;

    mAddressingFinished = false;
    mInstructionFinished = false;
    mFinished = false;
}

void Instruction::tick(MemoryBus *memoryBus, RegisterFile &rf)
{
    if(!mAddressingFinished){
        mAddressingFinished = addressingModeOperations[mInfo.addressingModeType](rf, memoryBus, mDecodedAddress, mAddressingCycle++);
    }else if(!mInstructionFinished){
        mInstructionFinished = instructionSetOperations[mInfo.instructionType](rf, memoryBus, mDecodedAddress, mInstructionCycle++);
    }
    mCurrentCycle++;
}

bool Instruction::isFinished()
{
    return mAddressingFinished && mInstructionFinished;
}

InstructionType Instruction::getType()
{
    return mInfo.instructionType;
}
