#include "Accumulator.h"

namespace V6502{ namespace AddressingModes{
Accumulator::Accumulator(){
    mDecoded = false;
}
Accumulator::~Accumulator(){}

void Accumulator::decodeTick(MemoryBus *bus, RegisterFile &rf){
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

}}