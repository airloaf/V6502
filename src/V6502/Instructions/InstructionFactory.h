#pragma once

#include <stdint.h>

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

enum AddressingModeType {
    ACCUMULATOR,
    IMMEDIATE,
    ABSOLUTE,
    ZERO_PAGE,
    ZERO_PAGE_X,
    ZERO_PAGE_Y,
    INDEXED_ABSOLUTE_X,
    INDEXED_ABSOLUTE_Y,
    IMPLIED,
    RELATIVE,
    INDEXED_INDIRECT,
    INDIRECT_INDEXED,
    ABSOLUTE_INDIRECT
};


struct InstructionMetaInfo {
    AddressingModeType addressingModeType;
    InstructionType instructionType; // The type of instruction
    int baseCycles; // The base number of cycles for the instruction
};

/**
 * @brief Create an Instruction based off the given opcode
 * 
 * @param opcode 
 * @return Instruction 
 */
InstructionMetaInfo fetchInstructionByOpcode(uint8_t opcode);