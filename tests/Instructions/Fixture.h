#pragma once

#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>

#include "../MemoryBus.h"

#include <iostream>

struct CPUFixture {
    // Memory bus for testing
    MemoryBus *bus;

    CPUFixture(){
        BOOST_TEST_MESSAGE("Fixture Constructor");
        bus = new MemoryBus();
        // Set the address bus to the CPU
        cpu.setAddressBus(bus);

        // Set the bus->address
        bus->write(0xFFFC, 0x00);
        bus->write(0xFFFD, 0x00);

        // Skip the first 6 cycles
        for(int i = 0; i < 6; i++){
            cpu.tick();
        }

    }
    ~CPUFixture(){}

    void setImmediate(uint8_t opcode, uint8_t value){
        bus->write(0x0000, opcode);
        bus->write(0x0001, value);
    }

    uint16_t setAbsolute(uint8_t opcode, uint16_t valueAddress, uint8_t value){
        bus->write(0x0000, opcode);
        bus->write(0x0001, (valueAddress & 0x00FF));
        bus->write(0x0002, ((valueAddress & 0xFF00) >> 4));
        bus->write(valueAddress, value);
        return valueAddress;
    }

    void setZeroPage(uint8_t opcode, uint8_t zeroPageAddress, uint8_t value){
        bus->write(0x0000, opcode);
        bus->write(0x0001, zeroPageAddress);
        bus->write(0x0100 + zeroPageAddress, value);
    }

    uint16_t setIndexedZeroPage(uint8_t opcode, uint8_t offset, uint8_t indexValue, uint8_t value){
        bus->write(0x0000, opcode);
        bus->write(0x0001, offset);
        uint16_t valueAddress = (0x0100 + offset + indexValue) % 0x0100;
        bus->write(valueAddress, value);
        return valueAddress;
    }

    uint16_t setIndexedAbsolute(uint8_t opcode, uint16_t address, uint8_t indexValue, uint8_t value){
        bus->write(0x0000, opcode);
        bus->write(0x0001, (address & 0x00FF));
        bus->write(0x0002, ((address & 0xFF00) >> 4));
        uint16_t valueAddress = address + indexValue;
        bus->write(valueAddress, value);
        return valueAddress;
    }

    uint16_t setRelative(uint8_t opcode, int8_t relative){
        bus->write(0x0000, opcode);
        bus->write(0x0001, relative);
        return (opcode + relative);
    }

    void execute(int cycles){
        for(int i = 0; i < cycles; i++){
            cpu.tick();
        }
    }

    // CPU
    V6502::CPU cpu;
};