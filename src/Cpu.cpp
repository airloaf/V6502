#include <V6502/CPU.h>

using namespace V6502;

void CPU::tick(){

}

void CPU::reset(){

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