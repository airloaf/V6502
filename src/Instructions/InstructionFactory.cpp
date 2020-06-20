#include "InstructionFactory.h"

#include "AddressingModes/Absolute.h"
#include "AddressingModes/Accumulator.h"
#include "AddressingModes/Immediate.h"
#include "AddressingModes/Implied.h"
#include "AddressingModes/IndexedAbsolute.h"
#include "AddressingModes/IndexedIndirect.h"
#include "AddressingModes/Relative.h"
#include "AddressingModes/ZeroPage.h"
#include "AddressingModes/ZeroPageIndexed.h"

using namespace V6502::AddressingModes;

struct InstructionMetaInfo {
    AddressingModeType addressingModeType; // The type of addressing mode to use
    InstructionType instructionType; // The type of instruction
    int baseCycles; // The base number of cycles for the instruction
};

InstructionMetaInfo instructionInfoTable[0x100] = {
/*        0                 1                        2                 3  4                   5                   6                   7  8               9                           A                   B  C                          D                          E                          F*/
/*0x0*/   {IMPLIED,  BRK,7},{INDEXED_INDIRECT,ORA,6},{},               {},{},                 {ZERO_PAGE,  ORA,3},{ZERO_PAGE,  ASL,5},{},{IMPLIED,PHP,3},{IMMEDIATE,ORA,2},          {ACCUMULATOR,ASL,2},{},{},                        {ABSOLUTE,          ORA,4},{ABSOLUTE,          ASL,6},{},
/*0x1*/   {RELATIVE, BPL,2},{INDIRECT_INDEXED,ORA,5},{},               {},{},                 {ZERO_PAGE_X,ORA,4},{ZERO_PAGE_X,ASL,6},{},{IMPLIED,CLC,2},{INDEXED_ABSOLUTE_Y, ORA,4},{},                 {},{},                        {INDEXED_ABSOLUTE_X,ORA,4},{INDEXED_ABSOLUTE_X,ASL,7},{},
/*0x2*/   {ABSOLUTE, JSR,6},{INDEXED_INDIRECT,AND,6},{},               {},{ZERO_PAGE,  BIT,3},{ZERO_PAGE,  AND,3},{ZERO_PAGE,  ROL,5},{},{IMPLIED,PLP,4},{IMMEDIATE,AND,2},          {ACCUMULATOR,ROL,2},{},{ABSOLUTE,          BIT,4},{ABSOLUTE,          AND,4},{ABSOLUTE,          ROL,6},{},
/*0x3*/   {RELATIVE, BMI,2},{INDIRECT_INDEXED,AND,5},{},               {},{},                 {ZERO_PAGE_X,AND,4},{ZERO_PAGE_X,ROL,6},{},{IMPLIED,SEC,2},{INDEXED_ABSOLUTE_Y, AND,4},{},                 {},{},                        {INDEXED_ABSOLUTE_X,AND,4},{INDEXED_ABSOLUTE_X,ROL,7},{},
/*0x4*/   {IMPLIED,  RTI,6},{INDEXED_INDIRECT,EOR,6},{},               {},{},                 {ZERO_PAGE,  EOR,3},{ZERO_PAGE,  LSR,5},{},{IMPLIED,PHA,3},{IMMEDIATE,EOR,2},          {ACCUMULATOR,LSR,2},{},{ABSOLUTE,          JMP,3},{ABSOLUTE,          EOR,4},{ABSOLUTE,          LSR,6},{},
/*0x5*/   {RELATIVE, BVC,2},{INDIRECT_INDEXED,EOR,5},{},               {},{},                 {ZERO_PAGE_X,EOR,4},{ZERO_PAGE_X,LSR,6},{},{IMPLIED,CLI,2},{INDEXED_ABSOLUTE_Y, EOR,4},{},                 {},{},                        {INDEXED_ABSOLUTE_X,EOR,4},{INDEXED_ABSOLUTE_X,LSR,7},{},
/*0x6*/   {IMPLIED,  RTS,6},{INDEXED_INDIRECT,ADC,6},{},               {},{},                 {ZERO_PAGE,  ADC,3},{ZERO_PAGE,  ROR,5},{},{IMPLIED,PLA,4},{IMMEDIATE,ADC,2},          {ACCUMULATOR,ROR,2},{},{ABSOLUTE_INDIRECT, JMP,5},{ABSOLUTE,          ADC,4},{ABSOLUTE,          ROR,6},{},
/*0x7*/   {RELATIVE, BVS,2},{INDIRECT_INDEXED,ADC,5},{},               {},{},                 {ZERO_PAGE_X,ADC,4},{ZERO_PAGE_X,ROR,6},{},{IMPLIED,SEI,2},{INDEXED_ABSOLUTE_Y, ADC,4},{},                 {},{},                        {INDEXED_ABSOLUTE_X,ADC,4},{INDEXED_ABSOLUTE_X,ROR,7},{},
/*0x8*/   {},               {INDEXED_INDIRECT,STA,6},{},               {},{ZERO_PAGE,  STY,3},{ZERO_PAGE,  STA,3},{ZERO_PAGE,  STX,3},{},{IMPLIED,DEY,2},{},                         {IMPLIED,    TXA,2},{},{ABSOLUTE,          STY,4},{ABSOLUTE,          STA,4},{ABSOLUTE,          STX,4},{},
/*0x9*/   {RELATIVE, BCC,2},{INDIRECT_INDEXED,STA,6},{},               {},{ZERO_PAGE_X,STY,4},{ZERO_PAGE_X,STA,4},{ZERO_PAGE_Y,STX,4},{},{IMPLIED,TYA,2},{INDEXED_ABSOLUTE_Y, STA,5},{IMPLIED,    TXS,2},{},{},                        {INDEXED_ABSOLUTE_X,STA,4},{},                        {},
/*0xA*/   {IMMEDIATE,LDY,2},{INDEXED_INDIRECT,LDA,6},{IMMEDIATE,LDX,2},{},{ZERO_PAGE,  LDY,3},{ZERO_PAGE,  LDA,3},{ZERO_PAGE,  LDX,3},{},{IMPLIED,TAY,2},{IMMEDIATE,LDA,2},          {IMPLIED,    TAX,2},{},{ABSOLUTE,          LDY,4},{ABSOLUTE,          LDA,4},{ABSOLUTE,          LDX,4},{},
/*0xB*/   {RELATIVE, BCS,2},{INDIRECT_INDEXED,LDA,5},{},               {},{ZERO_PAGE_X,LDY,4},{ZERO_PAGE_X,LDA,4},{ZERO_PAGE_Y,LDX,4},{},{IMPLIED,CLV,2},{INDEXED_ABSOLUTE_Y, LDA,4},{IMPLIED,    TSX,2},{},{INDEXED_ABSOLUTE_X,LDY,4},{INDEXED_ABSOLUTE_X,LDA,4},{INDEXED_ABSOLUTE_Y,LDX,4},{},
/*0xC*/   {IMMEDIATE,CPY,2},{INDEXED_INDIRECT,CMP,6},{},               {},{ZERO_PAGE,  CPY,3},{ZERO_PAGE,  CMP,3},{ZERO_PAGE,  DEC,5},{},{IMPLIED,INY,2},{IMMEDIATE,CMP,2},          {IMPLIED,    DEX,2},{},{ABSOLUTE,          CPY,4},{ABSOLUTE,          CMP,4},{ABSOLUTE,          DEC,6},{},
/*0xD*/   {RELATIVE, BNE,2},{INDIRECT_INDEXED,CMP,5},{},               {},{},                 {ZERO_PAGE_X,CMP,4},{ZERO_PAGE_X,DEC,6},{},{IMPLIED,CLD,2},{INDEXED_ABSOLUTE_Y, CMP,4},{},                 {},{},                        {INDEXED_ABSOLUTE_X,CMP,4},{INDEXED_ABSOLUTE_X,DEC,7},{},
/*0xE*/   {IMMEDIATE,CPX,2},{INDEXED_INDIRECT,SBC,6},{},               {},{ZERO_PAGE,  CPY,4},{ZERO_PAGE,  SBC,3},{ZERO_PAGE,  INC,5},{},{IMPLIED,INX,2},{IMMEDIATE,SBC,2},          {IMPLIED,    NOP,2},{},{ABSOLUTE,          CPX,4},{ABSOLUTE,          SBC,4},{ABSOLUTE,          INC,6},{},
/*0xF*/   {RELATIVE, BEQ,2},{INDIRECT_INDEXED,SBC,5},{},               {},{},                 {ZERO_PAGE_X,SBC,4},{ZERO_PAGE_X,INC,6},{},{IMPLIED,SED,2},{INDEXED_ABSOLUTE_Y, SBC,4},{},                 {},{},                        {INDEXED_ABSOLUTE_X,SBC,4},{INDEXED_ABSOLUTE_X,INC,7},{}
};

AddressingMode *createAddressingMode(AddressingModeType type){
    switch(type){
        case ACCUMULATOR:
            return new Accumulator();
        break; 
        case IMMEDIATE:
            return new Immediate();
        break;
        case ABSOLUTE:
            return new Absolute();
        break;
        case ZERO_PAGE:
            return new ZeroPage();
        break;
        case ZERO_PAGE_X:
            return new ZeroPageIndexed(true);
        break;
        case ZERO_PAGE_Y:
            return new ZeroPageIndexed(false);
        break;
        case INDEXED_ABSOLUTE_X:
            return new IndexedAbsolute(true);
            break;
        case INDEXED_ABSOLUTE_Y:
            return new IndexedAbsolute(false);
            break;
        case IMPLIED:
            return new Implied();
        break;
        case RELATIVE:
            return new Relative();
        break;
        case INDEXED_INDIRECT:
            return new IndexedIndirect();
        break;
        /*
        case INDIRECT_INDEXED:
        case ABSOLUTE_INDIRECT:
        */
        default:
            return new Implied();
        break;
    }
}

Instruction *createInstruction(uint8_t opcode){
    InstructionMetaInfo info = instructionInfoTable[opcode];
    AddressingMode *addressingMode = createAddressingMode(info.addressingModeType);
    return new Instruction(addressingMode, info.instructionType, info.baseCycles);
}