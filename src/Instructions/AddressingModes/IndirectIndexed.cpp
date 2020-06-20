#include "IndirectIndexed.h"

namespace V6502{ namespace AddressingModes{

IndirectIndexed::IndirectIndexed(): mCycle(0), mPageBoundaryCrossed(false) {}
IndirectIndexed::~IndirectIndexed(){}

void IndirectIndexed::decodeTick(AddressBus *bus, RegisterFile &rf){
    // 3-4 steps, get immediate value, add index value, return new value
    if(mCycle == 0){
        // Read the zero page address
        mTargetAddress = bus->read(rf.programCounter++);
    }else if(mCycle == 1){
        // Read the low byte of the return address
        mReturnAddress = bus->read(mTargetAddress);
    }else if(mCycle == 2){
        // Sum the low byte of the return address with indexY to check for page boundary collision
        uint16_t sum = mReturnAddress += rf.indexY;
        // Check for page boundary hit
        mPageBoundaryCrossed = ((sum & 0xFF00) != 0);

        // Read the high byte of the return address
        uint16_t highByte = (bus->read(mTargetAddress+1) << 8);
        // Calculate the current return address, the high byte, plus the low byte of the sum
        mReturnAddress = highByte | (sum & 0x00FF);
    }else if(mCycle == 3){
        // If we are still executing the address decoding, we must have hit a page boundary
        // Increment the page by one
        mReturnAddress += 0x100;
    }
    mCycle++;
}

uint16_t IndirectIndexed::getDecodedAddress(){
    return mReturnAddress;
}

bool IndirectIndexed::isFinished(){
    return (mCycle >= 3 && !mPageBoundaryCrossed) || (mCycle >= 4 && mPageBoundaryCrossed);
}

AddressingModeType IndirectIndexed::getType(){
    return AddressingModeType::INDEXED_INDIRECT;
}

bool IndirectIndexed::hasCrossedPageBoundary(){
    return mPageBoundaryCrossed;
}

}}