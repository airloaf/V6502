#pragma once

#include "InstructionFactory.h"
#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

using namespace V6502;

class Instruction{
    public:
        Instruction();
        ~Instruction();

        void init(InstructionMetaInfo instructionInfo);

        /**
         * @brief Executes a single cycle of the instruction
         */
        void tick(MemoryBus *memoryBus, RegisterFile &rf);

        /**
         * @brief Determines if the instruction has completed.
         * 
         * @return true 
         * @return false 
         */
        bool isFinished();

        /**
         * @brief Get the Instruction Type
         * 
         * @return InstructionType 
         */
        InstructionType getType();

    private:
        // Help function for status flags
        void setStatusFlagsFromValue(uint8_t value, RegisterFile &rf);

        // General arithmetic instruction (ALU)
        void arithmeticInstruction(MemoryBus *memoryBus, RegisterFile &rf);

        // General branch instruction
        void branchInstruction(MemoryBus *memoryBus, RegisterFile &rf);

        // Shift instructions
        void shiftInstruction(MemoryBus *memoryBus, RegisterFile &rf);

        // Register Instructions
        void registerInstruction(MemoryBus *memoryBus, RegisterFile &rf);

        // Load/Store Instructions
        void loadInstruction(MemoryBus *memoryBus, RegisterFile &rf);
        void storeInstructions(MemoryBus *memoryBus, RegisterFile &rf);

        // Push and Pull Instructions
        void pushInstruction(MemoryBus *memoryBus, RegisterFile &rf);
        void pullInstruction(MemoryBus *memoryBus, RegisterFile &rf);

        // Compare Instructions
        void compareInstruction(MemoryBus *memoryBus, RegisterFile &rf);

        // Setting/Clearing Instructions
        void setStatusInstructions(MemoryBus *memoryBus, RegisterFile &rf);
        void clearStatusInstructions(MemoryBus *memoryBus, RegisterFile &rf);

        // Transfer Instructions
        void transferInstructions(MemoryBus *memoryBus, RegisterFile &rf);

        // Jump Instructions
        void jumpInstructions(MemoryBus *memoryBus, RegisterFile &rf);

        // Memory Operation Instructions
        void memoryOperationInstructions(MemoryBus *memoryBus, RegisterFile &rf); 

        // Return Instructions 
        void returnInstructions(MemoryBus *memoryBus, RegisterFile &rf);

        // The different instructions we can execute
        void BIT(MemoryBus *memoryBus, RegisterFile &rf);
        void BRK(MemoryBus *memoryBus, RegisterFile &rf);
        void NOP(MemoryBus *memoryBus, RegisterFile &rf);

        void pushValueToStack(MemoryBus *memoryBus, RegisterFile &rf, uint8_t value);
        uint8_t pullValueFromStack(MemoryBus *memoryBus, RegisterFile &rf);

        // Addressing modes
        void AccumulatorAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void ImmediateAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void AbsoluteAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void ZeroPageAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void ZeroPageXAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void ZeroPageYAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void IndexedAbsoluteXAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void IndexedAbsoluteYAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void ImpliedAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void RelativeAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void IndexedIndirectAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void IndirectIndexedAddressing(MemoryBus *memoryBus, RegisterFile &rf);
        void AbsoluteIndirectAddressing(MemoryBus *memoryBus, RegisterFile &rf);

        // Fields 
        AddressingModeType mAddressingType; // The addressing mode for the current instruction
        InstructionType mType; // The instruction type
        int mBaseCycles; // The base number of instructions (not including page boundary crossing or when branch succeeds)

        int mCurrentCycle; // The current cycle for the instruction
        int mInstructionCycle; // The actual instruction cycle
        int mAddressingCycle;

        bool mAddressingFinished;
        bool mFinished;

        uint16_t mDecodedAddress;
        uint16_t mTempAddress;
};