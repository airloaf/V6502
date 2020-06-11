#include "Immediate.h"

Immediate::Immediate(){
    mDecoded = false;
}
Immediate::~Immediate(){}

void Immediate::decodeTick(AddressBus *bus, RegisterFile &rf){
    // Set the return address to the current program counter
    // Increment the program counter so that it is ready for the
    // next instruction fetch
    mReturnAddress = rf.programCounter++;

    mDecoded = true;
}

uint16_t Immediate::getDecodedAddress(){
    return mReturnAddress;
}

bool Immediate::isFinished(){
    return mDecoded;
}

AddressingModeType Immediate::getType(){
    return AddressingModeType::IMMEDIATE;
}