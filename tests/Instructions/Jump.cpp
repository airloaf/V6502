#include <boost/test/unit_test.hpp>

#include "Fixture.h"

BOOST_AUTO_TEST_SUITE(JUMP_INSTRUCTIONS)

/**
 * @brief Test BCC when carry is not set
 */
BOOST_FIXTURE_TEST_CASE(BCC_True, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x90, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setCarry(false);
    cpu.setRegisterFile(rf);
    execute(3);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BCC when carry was set
 */
BOOST_FIXTURE_TEST_CASE(BCC_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x90, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setCarry(true);
    cpu.setRegisterFile(rf);
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
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setCarry(true);
    cpu.setRegisterFile(rf);
    execute(3);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BCS when carry is not set
 */
BOOST_FIXTURE_TEST_CASE(BCS_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0xB0, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setCarry(false);
    cpu.setRegisterFile(rf);
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
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setZero(true);
    cpu.setRegisterFile(rf);
    execute(3);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BEQ when zero is not set
 */
BOOST_FIXTURE_TEST_CASE(BEQ_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0xF0, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setZero(false);
    cpu.setRegisterFile(rf);
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
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setNegative(true);
    cpu.setRegisterFile(rf);
    execute(3);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BMI when negative is not set
 */
BOOST_FIXTURE_TEST_CASE(BMI_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x30, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setNegative(false);
    cpu.setRegisterFile(rf);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

/**
 * @brief Test BNE when the result is negative (Negative and not zero)
 */
BOOST_FIXTURE_TEST_CASE(BNE_Negative, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0xD0, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setNegative(true);
    rf.setZero(false);
    cpu.setRegisterFile(rf);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BNE when the result is postiive (not negative and not zero)
 */
BOOST_FIXTURE_TEST_CASE(BNE_Positive, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0xD0, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setNegative(false);
    rf.setZero(false);
    cpu.setRegisterFile(rf);
    execute(3);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BNE when the result is Equal (zero is set)
 */
BOOST_FIXTURE_TEST_CASE(BNE_Equal, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0xD0, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setNegative(false);
    rf.setZero(true);
    cpu.setRegisterFile(rf);
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
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setNegative(false);
    rf.setZero(false);
    cpu.setRegisterFile(rf);
    execute(3);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BPL when the result is Equal (zero is set)
 */
BOOST_FIXTURE_TEST_CASE(BPL_Equal, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x10, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setNegative(false);
    rf.setZero(true);
    cpu.setRegisterFile(rf);
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
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setNegative(true);
    rf.setZero(false);
    cpu.setRegisterFile(rf);
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
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setOverflow(false);
    cpu.setRegisterFile(rf);
    execute(3);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BVC when the result is Equal (zero is set)
 */
BOOST_FIXTURE_TEST_CASE(BVC_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x50, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setOverflow(true);
    cpu.setRegisterFile(rf);
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
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setOverflow(true);
    cpu.setRegisterFile(rf);
    execute(3);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , nextPC);
}

/**
 * @brief Test BVS when the result is Equal (zero is set)
 */
BOOST_FIXTURE_TEST_CASE(BVS_False, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x70, 4);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.setOverflow(false);
    cpu.setRegisterFile(rf);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x0002);
}

BOOST_FIXTURE_TEST_CASE(JMP_Absolute, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.stackPointer = 0xFF;
    rf.programCounter = 0x0201;
    cpu.setRegisterFile(rf);

    bus->write(0x0201, 0x4C);
    bus->write(0x0202, 0x34);
    bus->write(0x0203, 0x12);
    execute(3);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x1234);
}

BOOST_FIXTURE_TEST_CASE(JMP_AbsoluteIndirect, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.stackPointer = 0xFF;
    rf.programCounter = 0x0201;
    cpu.setRegisterFile(rf);

    bus->write(0x0201, 0x6C);
    bus->write(0x0202, 0x34);
    bus->write(0x0203, 0x12);
    bus->write(0x1234, 0x10);
    bus->write(0x1235, 0xC9);
    execute(5);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0xC910);
}

BOOST_FIXTURE_TEST_CASE(JMP_AbsoluteIndirectBoundary, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.stackPointer = 0xFF;
    rf.programCounter = 0x0201;
    cpu.setRegisterFile(rf);

    bus->write(0x0201, 0x6C);
    bus->write(0x0202, 0xFF);
    bus->write(0x0203, 0x12);
    bus->write(0x12FF, 0x10);
    bus->write(0x1200, 0xC9);
    bus->write(0x1300, 0xF0);
    execute(5);
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0xC910);
}

BOOST_FIXTURE_TEST_CASE(JSR, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.stackPointer = 0xFF;
    rf.programCounter = 0x0201;
    cpu.setRegisterFile(rf);

    bus->write(0x0201, 0x20);
    bus->write(0x0202, 0x34);
    bus->write(0x0203, 0x12);

    execute(6);
    // Check that the program counter has been set properly
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x1234);
    // Program counter will be 0x204 - 1 on the stack
    BOOST_CHECK_EQUAL(bus->read(0x1FF), 0x02);
    BOOST_CHECK_EQUAL(bus->read(0x1FE), 0x03);
}

BOOST_FIXTURE_TEST_CASE(RTI, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.stackPointer = 0xFC;
    rf.programCounter = 0x0201;
    cpu.setRegisterFile(rf);

    // Store the instruction onto the bus
    bus->write(0x201, 0x40);

    // Store status and program counter
    bus->write(0x1FD, 0x49);
    bus->write(0x1FE, 0x34);
    bus->write(0x1FF, 0x12);

    execute(6);

    // Check that the program counter has been set properly
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x1234);

    // Check that the status register has been sent properly
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().status, 0x49);
}

BOOST_FIXTURE_TEST_CASE(RTS, CPUFixture){
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.stackPointer = 0xFC;
    rf.programCounter = 0x0201;
    cpu.setRegisterFile(rf);
    
    // Store the instruction onto the bus
    bus->write(0x201, 0x60);

    // Store status and program counter
    bus->write(0x1FD, 0x34);
    bus->write(0x1FE, 0x12);

    execute(6);

    // Check that the program counter has been set properly
    BOOST_CHECK_EQUAL(cpu.getRegisterFile().programCounter , 0x1234);
}

BOOST_AUTO_TEST_SUITE_END()