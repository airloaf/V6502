#include <boost/test/unit_test.hpp>

#include "Fixture.h"

BOOST_AUTO_TEST_SUITE(JUMP_INSTRUCTIONS)

/**
 * @brief Test BCC when carry is not set
 */
BOOST_FIXTURE_TEST_CASE(BCC_True, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x90, 4);
    cpu.getRegisterFile().setCarry(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BCC when carry was set
 */
BOOST_FIXTURE_TEST_CASE(BCC_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x90, 4);
    cpu.getRegisterFile().setCarry(true);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

/**
 * @brief Test BCS when carry is set
 */
BOOST_FIXTURE_TEST_CASE(BCS_True, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0xB0, 4);
    cpu.getRegisterFile().setCarry(true);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BCS when carry is not set
 */
BOOST_FIXTURE_TEST_CASE(BCS_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0xB0, 4);
    cpu.getRegisterFile().setCarry(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

/**
 * @brief Test BEQ when zero is set
 */
BOOST_FIXTURE_TEST_CASE(BEQ_True, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0xF0, 4);
    cpu.getRegisterFile().setZero(true);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BEQ when zero is not set
 */
BOOST_FIXTURE_TEST_CASE(BEQ_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0xF0, 4);
    cpu.getRegisterFile().setZero(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

/**
 * @brief Test BMI when negative is set
 */
BOOST_FIXTURE_TEST_CASE(BMI_True, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x30, 4);
    cpu.getRegisterFile().setNegative(true);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BMI when negative is not set
 */
BOOST_FIXTURE_TEST_CASE(BMI_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x30, 4);
    cpu.getRegisterFile().setNegative(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

/**
 * @brief Test BNE when the result is negative (Negative and not zero)
 */
BOOST_FIXTURE_TEST_CASE(BNE_Negative, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x30, 4);
    cpu.getRegisterFile().setNegative(true);
    cpu.getRegisterFile().setZero(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BNE when the result is postiive (not negative and not zero)
 */
BOOST_FIXTURE_TEST_CASE(BNE_Positive, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x30, 4);
    cpu.getRegisterFile().setNegative(false);
    cpu.getRegisterFile().setZero(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BNE when the result is Equal (zero is set)
 */
BOOST_FIXTURE_TEST_CASE(BNE_Equal, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x30, 4);
    cpu.getRegisterFile().setNegative(false);
    cpu.getRegisterFile().setZero(true);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

/**
 * @brief Test BPL when the result is postiive (not negative and not zero)
 */
BOOST_FIXTURE_TEST_CASE(BPL_Positive, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x10, 4);
    cpu.getRegisterFile().setNegative(false);
    cpu.getRegisterFile().setZero(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BPL when the result is Equal (zero is set)
 */
BOOST_FIXTURE_TEST_CASE(BPL_Equal, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x10, 4);
    cpu.getRegisterFile().setNegative(false);
    cpu.getRegisterFile().setZero(true);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

/**
 * @brief Test BPL when the result is Equal (zero is set)
 */
BOOST_FIXTURE_TEST_CASE(BPL_Negative, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x10, 4);
    cpu.getRegisterFile().setNegative(true);
    cpu.getRegisterFile().setZero(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

/**
 * @brief Test BVC when the result is postiive (not negative and not zero)
 */
BOOST_FIXTURE_TEST_CASE(BVC_True, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x50, 4);
    cpu.getRegisterFile().setOverflow(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BVC when the result is Equal (zero is set)
 */
BOOST_FIXTURE_TEST_CASE(BVC_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x50, 4);
    cpu.getRegisterFile().setOverflow(true);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

/**
 * @brief Test BVS when the result is postiive (not negative and not zero)
 */
BOOST_FIXTURE_TEST_CASE(BVS_True, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x70, 4);
    cpu.getRegisterFile().setOverflow(true);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BVS when the result is Equal (zero is set)
 */
BOOST_FIXTURE_TEST_CASE(BVS_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x70, 4);
    cpu.getRegisterFile().setOverflow(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

BOOST_FIXTURE_TEST_CASE(JMP_Absolute, CPUFixture){
    uint16_t nextPC = setAbsolute(0x4C, 0x1234, 0x12);
    execute(3);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x1234);
}

BOOST_FIXTURE_TEST_CASE(JSR, CPUFixture){
    uint16_t nextPC = setAbsolute(0x20, 0x1234, 0x12);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.stackPointer = 0x00;

    execute(3);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x1234);
    BOOST_CHECK_EQUAL(bus.memory[0x100], 0x00);
    BOOST_CHECK_EQUAL(bus.memory[0x101], 0x00);
}

// TODO: RTI
// TODO: RTS

BOOST_AUTO_TEST_SUITE_END()