#include "ZeroPage.h"

namespace V6502{ namespace AddressingModes{

ZeroPage::ZeroPage(): mCycle(0){}
ZeroPage::~ZeroPage(){}

void ZeroPage::decodeTick(AddressBus *bus, RegisterFile &rf){
    if(mCycle == 0){
        // Increment the address by one
        mReturnAddress = rf.programCounter++;
    }else if(mCycle == 1){
        // Read the address at the previous location
        mReturnAddress = bus->read(mReturnAddress);
    }
    mCycle++;
}

uint16_t ZeroPage::getDecodedAddress(){
    return mReturnAddress;
}

bool ZeroPage::isFinished(){
    return (mCycle == 2);
}

AddressingModeType ZeroPage::getType(){
    return AddressingModeType::ZERO_PAGE;
}

}}