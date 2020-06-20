#include "ZeroPageIndexed.h"

namespace V6502{ namespace AddressingModes{

ZeroPageIndexed::ZeroPageIndexed(bool useIndexX): mUseIndexX(useIndexX), mCycle(0){}
ZeroPageIndexed::~ZeroPageIndexed(){}

void ZeroPageIndexed::decodeTick(AddressBus *bus, RegisterFile &rf){
    // 3 steps, get immediate value, add index value, return new value
    if(mCycle == 0){
        mReturnAddress = bus->read(rf.programCounter++);
    }else if(mCycle == 1){
        uint8_t index = mUseIndexX? rf.indexX: rf.indexY;
        mReturnAddress += index;
    }else{
        mReturnAddress &=  0x00FF;
    }

    mCycle++;
}

uint16_t ZeroPageIndexed::getDecodedAddress(){
    return mReturnAddress;
}

bool ZeroPageIndexed::isFinished(){
    return mCycle == 3;
}

AddressingModeType ZeroPageIndexed::getType(){
    return AddressingModeType::RELATIVE;
}

}}