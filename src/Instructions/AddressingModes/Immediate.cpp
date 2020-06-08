#include "Immediate.h"

uint16_t Immediate::decode(AddressBus *bus, RegisterFile &rf){
    // This addressing mode will return the address directly after
    // the instruction its trying to execute, so just return the program counter.
    uint16_t ret = rf.programCounter;

    // increment the program counter by one, since we are returning the
    // address after the pc.
    rf.programCounter++;
    return ret;
}

bool isFinished(){
    // This addressing mode takes no time, always return true
    return true;
}

AddressingModeType getType(){
    return AddressingModeType::IMMEDIATE;
}