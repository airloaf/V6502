
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
    BOOST_CHECK_EQUAL(bus.memory[0x47], memoryValue-1);
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
    BOOST_CHECK_EQUAL(bus.memory[0x47], memoryValue+1);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero(), z);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative(), n);
}

// Data to use for the test
static auto LDA_ImmediateValue =    bdata::make({0x00, 0x73, 0xD7, 0xC4, 0xFF});
static auto LDA_Zero =              bdata::make({false, false, false, false, true});
static auto LDA_Negative =          bdata::make({false, false, true, true, false});
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
static auto LDX_Zero =              bdata::make({false, false, false, false, true});
static auto LDX_Negative =          bdata::make({false, false, true, true, false});
static auto LDX_DATA = LDX_ImmediateValue ^ LDX_Zero ^ LDX_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, LDX_Immediate, LDX_DATA, memoryValue, z, n){
    setImmediate(0xA2, memoryValue);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator, memoryValue);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative(), n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero(), z);
}

// Data to use for the test
static auto LDY_ImmediateValue =    bdata::make({0x00, 0x73, 0xD7, 0xC4, 0xFF});
static auto LDY_Zero =              bdata::make({false, false, false, false, true});
static auto LDY_Negative =          bdata::make({false, false, true, true, false});
static auto LDY_DATA = LDY_ImmediateValue ^ LDY_Zero ^ LDY_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, LDY_Immediate, LDY_DATA, memoryValue, z, n){
    setImmediate(0xA0, memoryValue);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator, memoryValue);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative(), n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero(), z);
}

BOOST_AUTO_TEST_SUITE_END()

// TODO: PHA
// TODO: PHP
// TODO: PLA
// TODO: PLP

// TODO: RTI
// TODO: RTS

// TODO: STA
// TODO: STX
// TODO: STY