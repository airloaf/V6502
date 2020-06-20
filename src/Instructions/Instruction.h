#pragma once

#include "AddressingModes/AddressingMode.h"

using namespace V6502::AddressingModes;
using namespace V6502;

/**
 * @brief Each of the 56 different instruction types for the 6502 processor
 * 
 */
enum InstructionType{
    ADC, AND, ASL, BCC, BCS, BEQ, BIT, BMI, BNE, BPL, BRK, BVC, BVS, CLC,
    CLD, CLI, CLV, CMP, CPX, CPY, DEC, DEX, DEY, EOR, INC, INX, INY, JMP,
    JSR, LDA, LDX, LDY, LSR, NOP, ORA, PHA, PHP, PLA, PLP, ROL, ROR, RTI,
    RTS, SBC, SEC, SED, SEI, STA, STX, STY, TAX, TAY, TSX, TXA, TXS, TYA
};

class Instruction{
    public:
        Instruction(AddressingMode *addressingMode, InstructionType type, int baseCycles);
        ~Instruction();

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

    private:

        // Check if the given instruction hit a page boundary during
        // the addressing mode. If the instruction has hit a page boundary
        // and its instruction type is affected by such a collision, we
        // will delay the instruction by one cycle.
        bool isDelayedByPageBoundary();

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

        // Fields 
        AddressingMode *mAddressingMode; // The addressing mode for the current instruction
        InstructionType mType; // The instruction type
        int mBaseCycles; // The base number of instructions (not including page boundary crossing or when branch succeeds)

        int mCurrentCycle; // The current cycle for the instruction
        int mInstructionCycle; // The actual instruction cycle
};