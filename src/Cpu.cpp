#include <V6502/CPU.h>

using namespace V6502;

void CPU::tick(){

}

void CPU::reset(){

}

void CPU::setAddressBus(AddressBus *addressBus){
    mAddressBus = addressBus;
}

bool CPU::getNMI(){
    return mNMI;
}

void CPU::setNMI(bool set){
    mNMI = set;
}

bool CPU::getIRQ(){
    return mIRQ;
}

void CPU::setIRQ(bool set){
    mIRQ = set;
}

RegisterFile CPU::getRegisterFile(){
    return mRegisterFile;
}

void CPU::setRegisterFile(RegisterFile rf){
    mRegisterFile = rf;
}