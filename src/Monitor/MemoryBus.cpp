#include "MemoryBus.h"

uint8_t MemoryBus::read(uint16_t address){
    return mDataStore[address];
}

void MemoryBus::write(uint16_t address, uint8_t value){
    mDataStore[address] = value;
}