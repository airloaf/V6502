
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(MEMORY_INSTRUCTIONS)

// Data to use for the test
static auto DEC_MemoryValue =   bdata::make({0x00, 0x73, 0xD7, 0xC4, 0x01});
static auto DEC_Zero =          bdata::make({false, false, false, false, true});
static auto DEC_Negative =      bdata::make({true, false, true, true, false});
static auto DEC_DATA = DEC_MemoryValue ^ DEC_Zero ^ DEC_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, DEC_ZeroPage, DEC_DATA, memoryValue, z, n){
    setZeroPage(0xC6, 0x47, memoryValue);
    execute(5);
    BOOST_CHECK_EQUAL(bus->read(0x47), (uint8_t) (memoryValue-1));
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero(), z);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative(), n);
}

// Data to use for the test
static auto INC_MemoryValue =   bdata::make({0x00, 0x73, 0xD7, 0xC4, 0xFF});
static auto INC_Zero =          bdata::make({false, false, false, false, true});
static auto INC_Negative =      bdata::make({false, false, true, true, false});
static auto INC_DATA = INC_MemoryValue ^ INC_Zero ^ INC_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, INC_ZeroPage, INC_DATA, memoryValue, z, n){
    setZeroPage(0xE6, 0x47, memoryValue);
    execute(5);
    BOOST_CHECK_EQUAL(bus->read(0x47), (uint8_t) (memoryValue+1));
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero(), z);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative(), n);
}

// Data to use for the test
static auto LDA_ImmediateValue =    bdata::make({0x00, 0x73, 0xD7, 0xC4, 0xFF});
static auto LDA_Zero =              bdata::make({true, false, false, false, false});
static auto LDA_Negative =          bdata::make({false, false, true, true, true});
static auto LDA_DATA = LDA_ImmediateValue ^ LDA_Zero ^ LDA_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, LDA_Immediate, LDA_DATA, memoryValue, z, n){
    setImmediate(0xA9, memoryValue);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator, memoryValue);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative(), n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero(), z);
}

// Data to use for the test
static auto LDX_ImmediateValue =    bdata::make({0x00, 0x73, 0xD7, 0xC4, 0xFF});
static auto LDX_Zero =              bdata::make({true, false, false, false, false});
static auto LDX_Negative =          bdata::make({false, false, true, true, true});
static auto LDX_DATA = LDX_ImmediateValue ^ LDX_Zero ^ LDX_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, LDX_Immediate, LDX_DATA, memoryValue, z, n){
    setImmediate(0xA2, memoryValue);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().indexX, memoryValue);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative(), n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero(), z);
}

// Data to use for the test
static auto LDY_ImmediateValue =    bdata::make({0x00, 0x73, 0xD7, 0xC4, 0xFF});
static auto LDY_Zero =              bdata::make({true, false, false, false, false});
static auto LDY_Negative =          bdata::make({false, false, true, true, true});
static auto LDY_DATA = LDY_ImmediateValue ^ LDY_Zero ^ LDY_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, LDY_Immediate, LDY_DATA, memoryValue, z, n){
    setImmediate(0xA0, memoryValue);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().indexY, memoryValue);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative(), n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero(), z);
}

BOOST_FIXTURE_TEST_CASE(PHA, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.accumulator = 0x34;
    rf.stackPointer = 0x00;
    cpu.setRegisterFile(rf);
    bus->write(0x0000, 0x48);
    execute(3);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().stackPointer, 0x01);
    BOOST_CHECK_EQUAL(bus->read(cpu.getRegisterFile().stackPointer-1), 0x34);
}

BOOST_FIXTURE_TEST_CASE(PHP, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.status = 0x34;
    rf.stackPointer = 0x00;
    cpu.setRegisterFile(rf);
    bus->write(0x0000, 0x08);
    execute(3);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().stackPointer, 0x01);
    BOOST_CHECK_EQUAL(bus->read(cpu.getRegisterFile().stackPointer-1), 0x34);
}

BOOST_FIXTURE_TEST_CASE(PLA, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.stackPointer = 0x01;
    bus->write(rf.stackPointer, 0x34);
    cpu.setRegisterFile(rf);
    bus->write(0x0000, 0x68);
    execute(4);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().stackPointer, 0x00);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator, 0x34);
}

BOOST_FIXTURE_TEST_CASE(PLP, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.stackPointer = 0x01;
    bus->write(rf.stackPointer, 0x34);
    cpu.setRegisterFile(rf);
    bus->write(0x0000,0x28);
    execute(4);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().stackPointer, 0x00);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().status, 0x34);
}

BOOST_FIXTURE_TEST_CASE(STA_Immediate, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.programCounter = 0x400;
    rf.accumulator = 0x12;
    bus->write(0x400, 0x85);
    bus->write(0x401, 0x2F);
    bus->write(0x02F, 0xD5);
    cpu.setRegisterFile(rf);
    execute(3);
    BOOST_CHECK_EQUAL(bus->read(0x02F), 0x12);
}

BOOST_FIXTURE_TEST_CASE(STX_Immediate, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.programCounter = 0x400;
    rf.indexX = 0x12;
    bus->write(0x400, 0x86);
    bus->write(0x401, 0x2F);
    bus->write(0x02F, 0xD5);
    cpu.setRegisterFile(rf);
    execute(3);
    BOOST_CHECK_EQUAL(bus->read(0x02F), 0x12);
}

BOOST_FIXTURE_TEST_CASE(STY_Immediate, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.programCounter = 0x400;
    rf.indexY= 0x12;
    bus->write(0x400, 0x84);
    bus->write(0x401, 0x2F);
    bus->write(0x02F, 0xD5);
    cpu.setRegisterFile(rf);
    execute(3);
    BOOST_CHECK_EQUAL(bus->read(0x02F), 0x12);
}

BOOST_AUTO_TEST_SUITE_END()