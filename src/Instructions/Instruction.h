#pragma once

#include "AddressingModes/AddressingMode.h"

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
        void tick();

        /**
         * @brief Determines if the instruction has completed.
         * 
         * @return true 
         * @return false 
         */
        bool isFinished();

    private:

        AddressingMode *mAddressingMode; // The addressing mode for the current instruction
        InstructionType mType; // The instruction type
        int mBaseCycles; // The base number of instructions (not including page boundary crossing or when branch succeeds)
};