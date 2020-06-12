#include "Relative.h"

namespace V6502{ namespace AddressingModes{

Relative::Relative(){
    mDecoded = false;
}
Relative::~Relative(){}

void Relative::decodeTick(AddressBus *bus, RegisterFile &rf){
    // Set the return address to the current program counter
    // Increment the program counter so that it is ready for the
    // next instruction fetch
    mReturnAddress = rf.programCounter++;

    mDecoded = true;
}

uint16_t Relative::getDecodedAddress(){
    return mReturnAddress;
}

bool Relative::isFinished(){
    return mDecoded;
}

AddressingModeType Relative::getType(){
    return AddressingModeType::IMMEDIATE;
}

}}