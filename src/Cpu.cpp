#include <V6502/CPU.h>
#include "p_CPU.h"

using namespace V6502;

CPU::CPU(){
    // Create a private implementation of the CPU
    implementation = new pimpl(); 
}

CPU::~CPU(){
    // Free implementation pointer
    delete implementation;
}

void CPU::tick(){
    implementation->tick();
}

void CPU::reset(){
    implementation->reset();
}

void CPU::setMemoryBus(MemoryBus *memoryBus){
    implementation->setMemoryBus(memoryBus);
}

bool CPU::getNMI(){
    return implementation->getNMI();
}

void CPU::setNMI(bool set){
    implementation->setNMI(set);
}

bool CPU::getIRQ(){
    return implementation->getIRQ();
}

void CPU::setIRQ(bool set){
    implementation->setIRQ(set);
}

RegisterFile CPU::getRegisterFile(){
    return implementation->getRegisterFile();
}

void CPU::setRegisterFile(RegisterFile rf){
    implementation->setRegisterFile(rf);
}