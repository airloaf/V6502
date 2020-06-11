#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(ARITHMETIC_INSTRUCTIONS)

/**
 * @brief Test the ADC instruction with immediate addressing
 *
 * ADC with immediate addressing opcode is 0x69.
 * We use the value of 10 as the immediate value. 2 cycles to execute
 * the instructions.
 */
BOOST_FIXTURE_TEST_CASE(ADC_Immediate, CPUFixture){
    for(int i = 0 ; i < 0x1000; i++){
        BOOST_TEST_MESSAGE(bus->read(i));
    }
    bus->write(0x00, 0x69);
    bus->write(0x01, 0x0A);
    execute(2);

    // Check that the accumulator is 10
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator , 0xA);
}

/**
 * @brief Test ADC with Zero Page
 * 
 * The instruction will fetch the zero page address and use that
 * value to add to the accumulator. The zero page instruction will
 * take 3 cycles to execute.
 */
BOOST_FIXTURE_TEST_CASE(ADC_ZP, CPUFixture){
    setZeroPage(0x65, 0x3F, 0x17);
    execute(3);

    // Check that the accumulator is 0x17
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator , 0x17);
}

/**
 * @brief Test AND with immediate 
 *
 * AND with immediate addressing opcode is 0x29.
 * Initial accumulator of 0xF7. Immediate of 0x18.
 * Accumulator should be 0x10.
 */
BOOST_FIXTURE_TEST_CASE(AND_Immediate, CPUFixture){
    setImmediate(0x29, 0x18);
    // Set the cpu accumulator to 0xF7
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.accumulator = 0xF7;
    cpu.setRegisterFile(rf);
    execute(2);

    // Check that the accumulator is 0x10
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator , 0x10);
}

/**
 * @brief Test ASL with the accumulator
 * 
 * ASL instruction is 0x0A. Initial accumualtor value
 * of 0xAA. After execution 0x55. 2 cycle execution.
 */
BOOST_FIXTURE_TEST_CASE(ASL_Accum, CPUFixture){
    // Store the instruction 0x0A in the memory
    bus->write(0x0000, 0x0A);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.accumulator = 0xAA;
    cpu.setRegisterFile(rf);
    execute(2);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator , 0x54);
}

// Data to use for the test
static auto EOR_MemoryValue =   bdata::make({0x00, 0x58, 0xCF, 0x7E});
static auto EOR_Accumulator =   bdata::make({0x00, 0x73, 0xD7, 0xCC});
static auto EOR_Result =        bdata::make({0x00, 0x2B, 0x18, 0xB2});
static auto EOR_Negative =      bdata::make({false, false, false, true});
static auto EOR_Zero =          bdata::make({true, false, false, false});
static auto EOR_DATA = EOR_MemoryValue ^ EOR_Accumulator ^ EOR_Result ^ EOR_Negative ^ EOR_Zero;

BOOST_DATA_TEST_CASE_F(CPUFixture, EOR_Immediate, EOR_DATA, memoryValue, accumulator, result, n, z){
    setImmediate(0x49, memoryValue);
    V6502::RegisterFile rf = cpu.getRegisterFile(); rf.accumulator = accumulator;
    cpu.setRegisterFile(rf);
    execute(2);

    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator , result);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative() , n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero() , z);
}

// Data to use for the test
static auto LSR_AccumulatorValue =  bdata::make({0x00, 0x73, 0xD7, 0xC4});
static auto LSR_Result =            bdata::make({0x00, 0x39, 0x6B, 0x62});
static auto LSR_Zero =              bdata::make({true, false, false, false});
static auto LSR_Carry =             bdata::make({false, true, true, false});
static auto LSR_DATA = LSR_AccumulatorValue ^ LSR_Result ^ LSR_Zero ^ LSR_Carry;

BOOST_DATA_TEST_CASE_F(CPUFixture, LSR_Accumulator, LSR_DATA, accumulatorValue, result, z, c){
    bus->write(0x0000, 0x4A);
    V6502::RegisterFile rf = cpu.getRegisterFile(); rf.accumulator = accumulatorValue;
    cpu.setRegisterFile(rf);
    execute(2);

    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator , result);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative() , false);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero() , z);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getCarry() , c);
}

BOOST_FIXTURE_TEST_CASE(NOP, CPUFixture){
    bus->write(0x0000, 0xEA);
    uint8_t oldAccumualtor = cpu.getRegisterFile().accumulator;
    execute(2);
    BOOST_CHECK_EQUAL(oldAccumualtor , cpu.getRegisterFile().accumulator);
}

// Data to use for the test
static auto ORA_MemoryValue =       bdata::make({0x00, 0x73, 0xD7, 0xC4});
static auto ORA_AccumulatorValue =  bdata::make({0x00, 0x73, 0xD7, 0xC4});
static auto ORA_Result =            bdata::make({0x00, 0x39, 0x6B, 0x62});
static auto ORA_Zero =              bdata::make({true, false, false, false});
static auto ORA_Negative =          bdata::make({false, true, true, false});
static auto ORA_DATA = ORA_MemoryValue ^ ORA_AccumulatorValue ^ ORA_Result ^ ORA_Zero ^ ORA_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, ORA_Immediate, ORA_DATA, immediate, accumulator, result, z, n){
    setImmediate(0x09, immediate);
    V6502::RegisterFile rf = cpu.getRegisterFile(); rf.accumulator = accumulator;
    cpu.setRegisterFile(rf);
    execute(2);

    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator , result);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative() , n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero() , z);
}

// Data to use for the test
static auto ROL_AccumulatorValue =  bdata::make({0x00, 0x73, 0xD7, 0xC4});
static auto ROL_Result =            bdata::make({0x00, 0xE6, 0xAE, 0x62});
static auto ROL_Zero =              bdata::make({true, false, false, false});
static auto ROL_Carry =             bdata::make({false, false, true, true});
static auto ROL_Negative =          bdata::make({false, true, true, true});
static auto ROL_DATA = ROL_AccumulatorValue ^ ROL_Result ^ ROL_Zero ^ ROL_Carry ^ ROL_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, ROL_Accumulator, ROL_DATA, accumulatorValue, result, z, c, n){
    bus->write(0x0000, 0x4A);
    V6502::RegisterFile rf = cpu.getRegisterFile(); rf.accumulator = accumulatorValue;
    cpu.setRegisterFile(rf);
    execute(2);

    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator , result);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative() , n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero() , z);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getCarry() , c);
}

// Data to use for the test
static auto ROR_AccumulatorValue =  bdata::make({0x00, 0x73, 0xD7, 0xC4});
static auto ROR_Result =            bdata::make({0x00, 0xB9, 0xEB, 0x62});
static auto ROR_Zero =              bdata::make({true, false, false, false});
static auto ROR_Carry =             bdata::make({false, true, true, false});
static auto ROR_Negative =          bdata::make({false, true, true, false});
static auto ROR_DATA = ROR_AccumulatorValue ^ ROR_Result ^ ROR_Zero ^ ROR_Carry ^ ROR_Negative;

BOOST_DATA_TEST_CASE_F(CPUFixture, ROR_Accumulator, ROR_DATA, accumulatorValue, result, z, c, n){
    bus->write(0x0000, 0x4A);
    V6502::RegisterFile rf = cpu.getRegisterFile(); rf.accumulator = accumulatorValue;
    cpu.setRegisterFile(rf);
    execute(2);

    BOOST_CHECK_EQUAL(cpu.getRegisterFile().accumulator , result);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getNegative() , n);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getZero() , z);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().getCarry() , c);
}

BOOST_AUTO_TEST_SUITE_END()

// TODO: SBC