#include "Absolute.h"

namespace V6502{ namespace AddressingModes{

Absolute::Absolute(): mCycle(0){}
Absolute::~Absolute(){}

void Absolute::decodeTick(AddressBus *bus, RegisterFile &rf){
    if(mCycle == 0){
        // Get the lower bits of the address
        mReturnAddress = bus->read(rf.programCounter++);
    }else if(mCycle == 1){
        // Read the upper bits of the address
        mReturnAddress += ((uint16_t) bus->read(rf.programCounter++)) << 8;
    }
    mCycle++;
}

uint16_t Absolute::getDecodedAddress(){
    return mReturnAddress;
}

bool Absolute::isFinished(){
    return (mCycle == 2);
}

AddressingModeType Absolute::getType(){
    return AddressingModeType::ABSOLUTE;
}

}}