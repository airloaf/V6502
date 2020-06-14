#pragma once

#include "AddressingModes/AddressingMode.h"

using namespace V6502::AddressingModes;

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
        void tick(AddressBus *addressBus, RegisterFile &rf);

        /**
         * @brief Determines if the instruction has completed.
         * 
         * @return true 
         * @return false 
         */
        bool isFinished();

    private:

        // Help function for status flags
        void setStatusFlagsFromValue(uint8_t value, RegisterFile &rf);

        // General arithmetic instruction (ALU)
        void arithmeticInstruction(AddressBus *addressBus, RegisterFile &rf);

        // General branch instruction
        void branchInstruction(AddressBus *addressBus, RegisterFile &rf);

        // Shift instructions
        void shiftInstruction(AddressBus *addressBus, RegisterFile &rf);

        // Register Instructions
        void registerInstruction(AddressBus *addressBus, RegisterFile &rf);

        // Load instructions
        void loadInstruction(AddressBus *addressBus, RegisterFile &rf);

        // Push and Pull Instructions
        void pushInstruction(AddressBus *addressBus, RegisterFile &rf);
        void pullInstruction(AddressBus *addressBus, RegisterFile &rf);

        // Compare Instructions
        void compareInstruction(AddressBus *addressBus, RegisterFile &rf);

        // Setting/Clearing Instructions
        void setStatusInstructions(AddressBus *addressBus, RegisterFile &rf);
        void clearStatusInstructions(AddressBus *addressBus, RegisterFile &rf);

        // Transfer Instructions
        void transferInstructions(AddressBus *addressBus, RegisterFile &rf);

        // Jump Instructions
        void jumpInstructions(AddressBus *addressBus, RegisterFile &rf);

        // Memory Operation Instructions
        void memoryOperationInstructions(AddressBus *addressBus, RegisterFile &rf); 

        // The different instructions we can execute
        void BIT(AddressBus *addressBus, RegisterFile &rf);
        void BRK(AddressBus *addressBus, RegisterFile &rf);
        void NOP(AddressBus *addressBus, RegisterFile &rf);
        void RTI(AddressBus *addressBus, RegisterFile &rf);
        void RTS(AddressBus *addressBus, RegisterFile &rf);
        void STA(AddressBus *addressBus, RegisterFile &rf);
        void STX(AddressBus *addressBus, RegisterFile &rf);
        void STY(AddressBus *addressBus, RegisterFile &rf);

        // Fields 
        AddressingMode *mAddressingMode; // The addressing mode for the current instruction
        InstructionType mType; // The instruction type
        int mBaseCycles; // The base number of instructions (not including page boundary crossing or when branch succeeds)

        int mCurrentCycle; // The current cycle for the instruction
        int mInstructionCycle; // The actual instruction cycle
};