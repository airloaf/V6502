#include "AbsoluteIndirect.h"

namespace V6502{ namespace AddressingModes{

AbsoluteIndirect::AbsoluteIndirect(): mCycle(0){}
AbsoluteIndirect::~AbsoluteIndirect(){}

void AbsoluteIndirect::decodeTick(MemoryBus *bus, RegisterFile &rf){
    if(mCycle == 0){
        mIndirectAddress = bus->read(rf.programCounter++);
    }else if(mCycle == 1){
        mIndirectAddress += (bus->read(rf.programCounter++) << 8);
    }else if(mCycle == 2){
        mReturnAddress = bus->read(mIndirectAddress);
    }else if(mCycle == 3){
        uint16_t highOrderBits = mIndirectAddress & 0xFF00;
        uint8_t incrementedAddress = (mIndirectAddress + 1);
        highOrderBits |= incrementedAddress;
        mReturnAddress += (bus->read(highOrderBits) << 8);
    }
    mCycle++;
}

uint16_t AbsoluteIndirect::getDecodedAddress(){
    return mReturnAddress;
}

bool AbsoluteIndirect::isFinished(){
    return (mCycle == 4);
}

AddressingModeType AbsoluteIndirect::getType(){
    return AddressingModeType::ABSOLUTE_INDIRECT;
}

}}