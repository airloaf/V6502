
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

BOOST_AUTO_TEST_SUITE_END()

// TODO: LDA
// TODO: LDX
// TODO: LDY
// TODO: PHA
// TODO: PHP
// TODO: PLA
// TODO: PLP
// TODO: RTI
// TODO: RTS
// TODO: STA
// TODO: STX
// TODO: STY