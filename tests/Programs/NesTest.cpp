#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>

#include "NesFixture.h"

BOOST_AUTO_TEST_SUITE(program_tests)

BOOST_FIXTURE_TEST_CASE(NESTest, NESFixture){

    // Execute the first 6 ticks
    for(int i = 0; i < 6; i++){cpu.tick();}

    // Get the CPU register file
    V6502::RegisterFile rf = cpu.getRegisterFile();
    // set the program counter to 0xC000
    rf.programCounter = 0xC000;

    // Set the cpu to the register file
    cpu.setRegisterFile(rf);

    // Load the nes test rom
    readFile("tests/test_data/nestest.nes");

    // Run this program for a while
    for(int i = 0; i < 100000000; i++){
        cpu.tick();
    }

    // Expect that these two values are 0
    BOOST_CHECK_EQUAL(bus->read(0x02), 0x00);
    BOOST_CHECK_EQUAL(bus->read(0x03), 0x00);
}

BOOST_AUTO_TEST_SUITE_END()