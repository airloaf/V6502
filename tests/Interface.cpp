#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>
#include <V6502/AddressBus.h>

#include "MemoryBus.h"

BOOST_AUTO_TEST_SUITE(cpu_instruction_tests)

struct CPUFixture {
    CPUFixture(){cpu.setAddressBus(&bus);}
    ~CPUFixture(){}

    // CPU
    V6502::CPU cpu;

    // Memory bus for testing
    MemoryBus bus;
};

/**
 * @brief Test that the cpu starts up properly
 * 
 * On startup the CPU will load the program counter
 * from 0xFFFC and 0xFFFD
 */
BOOST_FIXTURE_TEST_CASE(CPU_Startup, CPUFixture){
    // Setup the program counter memory location
    bus.memory[0xFFFC] = 0x34;
    bus.memory[0xFFFD] = 0x12;

    // The reset command takes 6 cycles to fully perform
    for(int i = 0; i < 6; i++){
        cpu.tick();
    }

    // Check if the program counter is set to 0x1234 as set by the memory
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x1234);

    // Check that the interrupt mask is set
    BOOST_CHECK((cpu.getRegisterFile().status & 0x4) != 0);
}

/**
 * @brief Test that the cpu will reset after 6 cycles of calling reset
 * 
 * On reset, as well as on startup, the CPU will laod the program counter
 * from 0xFFFC and 0xFFFD. Similarly the interrupt mask will be set
 */
BOOST_FIXTURE_TEST_CASE(CPU_Reset, CPUFixture){
    // Set the initial program counter to 0000
    bus.memory[0xFFFC] = 0x00;
    bus.memory[0xFFFD] = 0x00;

    // Startup takes 6 cycles to fully perform
    for(int i = 0; i < 6; i++){
        cpu.tick();
    }

    // Check if the program counter is set to 0x0000 as set by the memory
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0000);

    // Check that the interrupt mask is set
    BOOST_CHECK((cpu.getRegisterFile().status & 0x4) != 0);

    // Set the program counter to be a different value
    bus.memory[0xFFFC] = 0x34;
    bus.memory[0xFFFD] = 0x12;
    
    // Rest takes 6 cycles to fully perform
    for(int i = 0; i < 6; i++){
        cpu.tick();
    }
    
    // Check if the program counter is set to 0x1234 as set by the memory
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x1234);

    // Check that the interrupt mask is set
    BOOST_CHECK((cpu.getRegisterFile().status & 0x4) != 0);
}

BOOST_AUTO_TEST_SUITE_END()