#include "IndexedIndirect.h"

namespace V6502{ namespace AddressingModes{

IndexedIndirect::IndexedIndirect(): mCycle(0) {}
IndexedIndirect::~IndexedIndirect(){}

void IndexedIndirect::decodeTick(MemoryBus *bus, RegisterFile &rf){
    // 3-4 steps, get immediate value, add index value, return new value
    if(mCycle == 0){
        // Read the zero page address
        mTargetAddress = bus->read(rf.programCounter++);
    }else if(mCycle == 1){
        // Add the value from the indexX register
        mTargetAddress += rf.indexX;
        // Remove the carry
        mTargetAddress &= 0x00FF;
    }else if(mCycle == 2){
        // Read the low bits of the address
        mReturnAddress = bus->read(mTargetAddress);
    }else if(mCycle == 3){
        // Read the high bits of the address
        mReturnAddress += (bus->read(mTargetAddress+1) << 8);
    }

    mCycle++;
}

uint16_t IndexedIndirect::getDecodedAddress(){
    return mReturnAddress;
}

bool IndexedIndirect::isFinished(){
    return (mCycle == 4);
}

AddressingModeType IndexedIndirect::getType(){
    return AddressingModeType::INDEXED_INDIRECT;
}

}}