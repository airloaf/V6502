#include <boost/test/unit_test.hpp>

#include "Fixture.h"

BOOST_AUTO_TEST_SUITE(ARITHMETIC_INSTRUCTIONS)

/**
 * @brief Test the ADC instruction with immediate addressing
 *
 * ADC with immediate addressing opcode is 0x69.
 * We use the value of 10 as the immediate value. 2 cycles to execute
 * the instructions.
 */
BOOST_FIXTURE_TEST_CASE(ADC_Immediate, CPUFixture){
    setImmediate(0x69, 0x0A);
    execute(2);

    // Check that the accumulator is 10
    BOOST_CHECK(cpu.getRegisterFile().accumulator == 0xA);
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
    BOOST_CHECK(cpu.getRegisterFile().accumulator == 0x17);
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
    BOOST_CHECK(cpu.getRegisterFile().accumulator == 0x10);
}

/**
 * @brief Test ASL with the accumulator
 * 
 * ASL instruction is 0x0A. Initial accumualtor value
 * of 0xAA. After execution 0x55. 2 cycle execution.
 */
BOOST_FIXTURE_TEST_CASE(ASL_Accum, CPUFixture){
    // Store the instruction 0x0A in the memory
    bus.memory[0x0000] = 0x0A;
    execute(2);
    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.accumulator = 0xAA;
    cpu.setRegisterFile(rf);
    BOOST_CHECK(cpu.getRegisterFile().accumulator == 0x55);
}

BOOST_AUTO_TEST_SUITE_END()
// TODO: EOR
// TODO: LSR (Accumulator)
// TODO: ORA
// TODO: ROL (Accumulator)
// TODO: ROR (Accumulator)
// TODO: SBC