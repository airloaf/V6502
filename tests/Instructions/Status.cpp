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
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getCarry(), false);
}

/**
 * @brief Test CLD
 */
BOOST_FIXTURE_TEST_CASE(CLD, CPUFixture){
    bus.memory[0x0000] = 0x18;
    cpu.getRegisterFile().setDecimalMode(true);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getDecimalMode(), false);
}

/**
 * @brief Test CLI
 */
BOOST_FIXTURE_TEST_CASE(CLI, CPUFixture){
    bus.memory[0x0000] = 0x18;
    cpu.getRegisterFile().setIRQDisable(true);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getIRQDisable(), false);
}

/**
 * @brief Test CLV
 */
BOOST_FIXTURE_TEST_CASE(CLV, CPUFixture){
    bus.memory[0x0000] = 0x18;
    cpu.getRegisterFile().setOverflow(true);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getOverflow(), false);
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
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative() , n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero() , z);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getCarry() , c);
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
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative() , n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero() , z);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getCarry() , c);
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
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative() , n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero() , z);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getCarry() , c);
}

/**
 * @brief Test BRK
 */
BOOST_FIXTURE_TEST_CASE(BRK, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.programCounter = 0x0008;
    rf.stackPointer = 0xFF;
    rf.status = 0xCF;
    cpu.setRegisterFile(rf);
    bus.memory[0x0008] = 0x00;
    execute(7);

    BOOST_CHECK_EQUAL(bus.memory[0x01FF], 0x08);
    BOOST_CHECK_EQUAL(bus.memory[0x01FE], 0x00);
    BOOST_CHECK_EQUAL(bus.memory[0x01FE], 0xCF);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getBRKCommand(), true);
}

/**
 * @brief Test SEC
 */
BOOST_FIXTURE_TEST_CASE(SEC, CPUFixture){
    bus.memory[0x0000] = 0x38;
    cpu.getRegisterFile().setCarry(false);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getCarry(), true);
}

/**
 * @brief Test SED
 */
BOOST_FIXTURE_TEST_CASE(SED, CPUFixture){
    bus.memory[0x0000] = 0xF8;
    cpu.getRegisterFile().setDecimalMode(false);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getDecimalMode(), true);
}

/**
 * @brief Test SEI
 */
BOOST_FIXTURE_TEST_CASE(SEI, CPUFixture){
    bus.memory[0x0000] = 0x78;
    cpu.getRegisterFile().setIRQDisable(false);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getIRQDisable(), true);
}

BOOST_AUTO_TEST_SUITE_END()

// TODO: BIT