#include "Implied.h"

namespace V6502{ namespace AddressingModes{

Implied::Implied(){
    mDecoded = false;
}
Implied::~Implied(){}

void Implied::decodeTick(AddressBus *bus, RegisterFile &rf){
    mDecoded = true;
}

uint16_t Implied::getDecodedAddress(){
    return 0x00;
}

bool Implied::isFinished(){
    return mDecoded;
}

AddressingModeType Implied::getType(){
    return AddressingModeType::IMPLIED;
}

}}