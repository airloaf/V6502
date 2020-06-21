#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>

#include "MemoryBus.h"

BOOST_AUTO_TEST_SUITE(cpu_instruction_tests)

struct CPUFixture {
    CPUFixture(){cpu.setMemoryBus(&bus);}
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
    bus.write(0xFFFC, 0x34);
    bus.write(0xFFFD, 0x12);

    // The reset command takes 6 cycles to fully perform
    for(int i = 0; i < 6; i++){
        cpu.tick();
    }

    // Expect that the stack pointer starts at 0xFF
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().stackPointer, 0xFF);

    // Check if the program counter is set to 0x1234 as set by the memory
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x1234);

    // Check that the status register is set properly
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().status, 0x24);
}

/**
 * @brief Test that the cpu will reset after 6 cycles of calling reset
 * 
 * On reset, as well as on startup, the CPU will laod the program counter
 * from 0xFFFC and 0xFFFD. Similarly the interrupt mask will be set
 */
BOOST_FIXTURE_TEST_CASE(CPU_Reset, CPUFixture){
    // Set the initial program counter to 0000
    bus.write(0xFFFC,0x00);
    bus.write(0xFFFD,0x00);

    // Startup takes 6 cycles to fully perform
    for(int i = 0; i < 6; i++){
        cpu.tick();
    }

    // Check if the program counter is set to 0x0000 as set by the memory
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter, 0x0000);

    // Check that the interrupt mask is set
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().status, 0x24);

    // Expect that the stack pointer starts at 0xFF
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().stackPointer, 0xFF);

    // Set the program counter to be a different value
    bus.write(0xFFFC, 0x34);
    bus.write(0xFFFD, 0x12);

    // Set the reset flag
    cpu.reset();
    
    // Rest takes 6 cycles to fully perform
    for(int i = 0; i < 6; i++){
        cpu.tick();
    }

    // Expect that the stack pointer starts at 0xFF
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().stackPointer, 0xFF);
    
    // Check if the program counter is set to 0x1234 as set by the memory
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter, 0x1234);

    // Check that the status register is set
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().status, 0x24);
}

struct InterruptFixture {
    InterruptFixture(){
        cpu.setMemoryBus(&bus);
        // Program Start at 0x300, Interrupt handler at 0x400, NMI interrupt at 0x500
        bus.write(0xFFFB, 0x05); bus.write(0xFFFA, 0x00);
        bus.write(0xFFFD, 0x03); bus.write(0xFFFC, 0x00);
        bus.write(0xFFFF, 0x04); bus.write(0xFFFE, 0x00);
        for(int i = 0; i < 6; i++){cpu.tick();}
    }
    ~InterruptFixture(){}
    // CPU and Memory Bus
    V6502::CPU cpu;
    MemoryBus bus;
};

BOOST_FIXTURE_TEST_CASE(CPU_IRQ_BASIC, InterruptFixture){

    // Write the interrupt handler
    // Load 0x47 into A
    // Add 0x23 to A
    // Return from interrupt
    bus.write(0x400, 0xA9);
    bus.write(0x401, 0x47);
    bus.write(0x402, 0x69);
    bus.write(0x403, 0x23);
    bus.write(0x404, 0x40);
    bus.write(0x405, 0x00);

    // Initiate an interrupt request
    cpu.setIRQ(true);

    V6502::RegisterFile rf = cpu.getRegisterFile(); rf.status = 0xC0;
    cpu.setRegisterFile(rf);

    // Execute the interrupt sequence (7 ticks)
    for(int i = 0; i < 7; i++){cpu.tick();}

    // Verify the program counter is now at the first instruction at the interrupt handler
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter, 0x400);
    // Verify that the disable interrupt request bit is set
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getIRQDisable(), true);

    // Execute the next two instructions
    for(int i = 0; i < 4; i++){cpu.tick();}

    // Check that the accumulator is now 0x6A
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator, 0x6A);
    
    // Execute the return from interrupt instruction
    for(int i = 0; i < 5; i++){cpu.tick();}
    
    // Check that the program counter is back to 0x300
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter, 0x300);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().status, 0xC0);
}

BOOST_FIXTURE_TEST_CASE(CPU_IRQ_IRQ_DISABLED, InterruptFixture){

    // Write the interrupt handler
    // Load 0x47 into A
    // Add 0x23 to A
    // Return from interrupt
    bus.write(0x400, 0xA9);
    bus.write(0x401, 0x47);
    bus.write(0x402, 0x69);
    bus.write(0x403, 0x23);
    bus.write(0x404, 0x40);
    bus.write(0x405, 0x00);

    // Place and execute the SEI instruction
    bus.write(0x300, 0x78);
    for(int i = 0; i < 2; i++){cpu.tick();}

    // 4 NOP instructions to eat up 8 ticks 
    bus.write(0x301, 0xEA);
    bus.write(0x302, 0xEA);
    bus.write(0x303, 0xEA);
    bus.write(0x304, 0xEA);

    // initiate an IRQ interrupt
    cpu.setIRQ(true);

    // Execute 7 ticks (equivalent to the interrupt sequence)
    for(int i = 0; i < 7; i++){cpu.tick();}

    // Verify the program counter is not in the first instruction at the interrupt handler
    // We will check that the page is still at page 0x300 instead of page 0x400
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter & 0xFF00, 0x300);
}

BOOST_FIXTURE_TEST_CASE(CPU_NMI_BASIC, InterruptFixture){

    // Write the interrupt handler
    // Load 0x47 into A
    // Add 0x23 to A
    // Return from interrupt
    bus.write(0x500, 0xA9);
    bus.write(0x501, 0x47);
    bus.write(0x502, 0x69);
    bus.write(0x503, 0x23);
    bus.write(0x504, 0x40);
    bus.write(0x505, 0x00);

    // Initiate an interrupt request
    cpu.setNMI(true);

    V6502::RegisterFile rf = cpu.getRegisterFile(); rf.status = 0xC0;
    cpu.setRegisterFile(rf);

    // Execute the interrupt sequence (7 ticks)
    for(int i = 0; i < 7; i++){cpu.tick();}

    // Verify the program counter is now at the first instruction at the interrupt handler
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter, 0x400);

    // Execute the next two instructions
    for(int i = 0; i < 4; i++){cpu.tick();}

    // Check that the accumulator is now 0x6A
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator, 0x6A);
    
    // Execute the return from interrupt instruction
    for(int i = 0; i < 5; i++){cpu.tick();}
    
    // Check that the program counter is back to 0x300
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter, 0x300);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().status, 0xC0);
}

BOOST_FIXTURE_TEST_CASE(CPU_NMI_IRQ_DISABLED, InterruptFixture){

    // Write the interrupt handler
    // Load 0x47 into A
    // Add 0x23 to A
    // Return from interrupt
    bus.write(0x500, 0xA9);
    bus.write(0x501, 0x47);
    bus.write(0x502, 0x69);
    bus.write(0x503, 0x23);
    bus.write(0x504, 0x40);
    bus.write(0x505, 0x00);

    // Place and execute the SEI instruction
    bus.write(0x300, 0x78);
    for(int i = 0; i < 2; i++){cpu.tick();}

    // initiate an IRQ interrupt
    cpu.setNMI(true);

    // Execute the interrupt sequence (7 ticks)
    for(int i = 0; i < 7; i++){cpu.tick();}

    // Verify the program counter is now at the first instruction at the interrupt handler
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter, 0x400);

    // Execute the next two instructions
    for(int i = 0; i < 4; i++){cpu.tick();}

    // Check that the accumulator is now 0x6A
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator, 0x6A);
    
    // Execute the return from interrupt instruction
    for(int i = 0; i < 5; i++){cpu.tick();}
    
    // Check that the program counter is back to 0x301
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter, 0x301);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().status, 0xC0);
}

BOOST_AUTO_TEST_SUITE_END()