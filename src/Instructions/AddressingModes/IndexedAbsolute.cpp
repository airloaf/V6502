#include "IndexedAbsolute.h"

namespace V6502{ namespace AddressingModes{

IndexedAbsolute::IndexedAbsolute(bool useIndexX): mUseIndexX(useIndexX), mCycle(0), mPageBoundaryCrossed(false){}
IndexedAbsolute::~IndexedAbsolute(){}

void IndexedAbsolute::decodeTick(MemoryBus *bus, RegisterFile &rf){
    // 3-4 steps, get immediate value, add index value, return new value
    if(mCycle == 0){
        mReturnAddress = bus->read(rf.programCounter++);
    }else if(mCycle == 1){
        mReturnAddress += (bus->read(rf.programCounter++) << 8);
    }else if(mCycle == 2){
        uint8_t index = mUseIndexX? rf.indexX: rf.indexY;
        uint16_t nextAddress = mReturnAddress + index;

        mPageBoundaryCrossed = ((mReturnAddress & 0xFF00) != (nextAddress & 0xFF00));
        mReturnAddress = nextAddress;
    }

    mCycle++;
}

uint16_t IndexedAbsolute::getDecodedAddress(){
    return mReturnAddress;
}

bool IndexedAbsolute::isFinished(){
    return (mCycle >= 3 && !mPageBoundaryCrossed) || (mCycle >= 4 && mPageBoundaryCrossed);
}

AddressingModeType IndexedAbsolute::getType(){
    return mUseIndexX? AddressingModeType::INDEXED_ABSOLUTE_X: AddressingModeType::INDEXED_ABSOLUTE_Y;
}

bool IndexedAbsolute::hasCrossedPageBoundary(){
    return mPageBoundaryCrossed;
}

}}