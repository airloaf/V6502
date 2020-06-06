#pragma once
#include <V6502/AddressBus.h>

class MemoryBus: public V6502::AddressBus{
    public:
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
        uint8_t memory[0x10000];
};