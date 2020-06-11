#include "Accumulator.h"

Accumulator::Accumulator(){
    mDecoded = false;
}
Accumulator::~Accumulator(){}

void Accumulator::decodeTick(AddressBus *bus, RegisterFile &rf){
    // The accumulator addressing mode does not need to do much.
    // We use 0 as the return address arbitrarily
    mReturnAddress = 0;
    mDecoded = true;
}

uint16_t Accumulator::getDecodedAddress(){
    return mReturnAddress;
}

bool Accumulator::isFinished(){
    return mDecoded;
}

AddressingModeType Accumulator::getType(){
    return AddressingModeType::ACCUMULATOR;
}