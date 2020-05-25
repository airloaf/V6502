#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(STATUS_REGISTER_INSTRUCTIONS)

/**
 * @brief Test CLC
 */
BOOST_FIXTURE_TEST_CASE(CLC, CPUFixture){
    bus.memory[0x0000] = 0x18;
    cpu.getRegisterFile().setCarry(true);
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().getCarry() == false);
}

/**
 * @brief Test CLD
 */
BOOST_FIXTURE_TEST_CASE(CLD, CPUFixture){
    bus.memory[0x0000] = 0x18;
    cpu.getRegisterFile().setDecimalMode(true);
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().getDecimalMode() == false);
}

/**
 * @brief Test CLI
 */
BOOST_FIXTURE_TEST_CASE(CLI, CPUFixture){
    bus.memory[0x0000] = 0x18;
    cpu.getRegisterFile().setIRQDisable(true);
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().getIRQDisable() == false);
}

/**
 * @brief Test CLV
 */
BOOST_FIXTURE_TEST_CASE(CLV, CPUFixture){
    bus.memory[0x0000] = 0x18;
    cpu.getRegisterFile().setOverflow(true);
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().getOverflow() == false);
}

// Data to use for the test
static auto CMP_MemoryValue =          bdata::make({0x00, 0x58, 0xCF, 0x7E});
static auto CMP_AccumulatorValue =     bdata::make({0x00, 0x01, 0xD7, 0x7E});
static auto CMP_Negative =             bdata::make({false, true, false, false});
static auto CMP_Zero =                 bdata::make({true, false, false, true});
static auto CMP_Carry =                bdata::make({true, true, false, true});
static auto CMP_DATA = CMP_MemoryValue ^ CMP_AccumulatorValue ^ CMP_Negative ^ CMP_Zero ^ CMP_Carry;

BOOST_DATA_TEST_CASE_F(CPUFixture, CMP_Immediate, CMP_DATA, memory, accumulator, n, z, c){
    setImmediate(0xC9, memory);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.accumulator = accumulator;
    cpu.setRegisterFile(rf);
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().getNegative() == n);
    BOOST_CHECK(cpu.getRegisterFile().getZero() == z);
    BOOST_CHECK(cpu.getRegisterFile().getCarry() == c);
}

// Data to use for the test
static auto CPX_MemoryValue =          bdata::make({0x00, 0x58, 0xCF, 0x7E});
static auto CPX_IndexValue =           bdata::make({0x00, 0x01, 0xD7, 0x7E});
static auto CPX_Negative =             bdata::make({false, true, false, false});
static auto CPX_Zero =                 bdata::make({true, false, false, true});
static auto CPX_Carry =                bdata::make({true, true, false, true});
static auto CPX_DATA = CPX_MemoryValue ^ CPX_IndexValue ^ CPX_Negative ^ CPX_Zero ^ CPX_Carry;

BOOST_DATA_TEST_CASE_F(CPUFixture, CPX_Immediate, CPX_DATA, memory, index, n, z, c){
    setImmediate(0xC9, memory);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.indexX = index;
    cpu.setRegisterFile(rf);
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().getNegative() == n);
    BOOST_CHECK(cpu.getRegisterFile().getZero() == z);
    BOOST_CHECK(cpu.getRegisterFile().getCarry() == c);
}

// Data to use for the test
static auto CPY_MemoryValue =          bdata::make({0x00, 0x58, 0xCF, 0x7E});
static auto CPY_IndexValue =           bdata::make({0x00, 0x01, 0xD7, 0x7E});
static auto CPY_Negative =             bdata::make({false, true, false, false});
static auto CPY_Zero =                 bdata::make({true, false, false, true});
static auto CPY_Carry =                bdata::make({true, true, false, true});
static auto CPY_DATA = CPY_MemoryValue ^ CPY_IndexValue ^ CPY_Negative ^ CPY_Zero ^ CPY_Carry;

BOOST_DATA_TEST_CASE_F(CPUFixture, CPY_Immediate, CPY_DATA, memory, index, n, z, c){
    setImmediate(0xC9, memory);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.indexY = index;
    cpu.setRegisterFile(rf);
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().getNegative() == n);
    BOOST_CHECK(cpu.getRegisterFile().getZero() == z);
    BOOST_CHECK(cpu.getRegisterFile().getCarry() == c);
}

BOOST_AUTO_TEST_SUITE_END()

// TODO: BIT
// TODO: BRK
// TODO: NOP
// TODO: SEC
// TODO: SED
// TODO: SEI