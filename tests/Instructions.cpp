#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>

#include "MemoryBus.h"

// TODO: BIT
// TODO: BRK 
// TODO: CMP
// TODO: CPX
// TODO: CPY
// TODO: DEC
// TODO: DEX
// TODO: DEY
// TODO: EOR
// TODO: INC
// TODO: INX
// TODO: INY
// TODO: JMP
// TODO: JSR
// TODO: LDA
// TODO: LDX
// TODO: LDY
// TODO: LSR
// TODO: NOP
// TODO: ORA
// TODO: PHA
// TODO: PHP
// TODO: PLA
// TODO: PLP
// TODO: ROL
// TODO: ROR
// TODO: RTI
// TODO: RTS
// TODO: SBC
// TODO: SEC
// TODO: SED
// TODO: SEI
// TODO: STA
// TODO: STX
// TODO: STY
// TODO: TAX
// TODO: TAY
// TODO: TSX
// TODO: TXA
// TODO: TXS
// TODO: TYA

BOOST_AUTO_TEST_SUITE(cpu_instruction_tests)

struct CPUFixture {
    CPUFixture(){
        // Set the address bus to the CPU
        cpu.setAddressBus(&bus);

        // Set the bus address
        bus.memory[0xFFFC] = 0x00;
        bus.memory[0xFFFD] = 0x00;

        // Skip the first 6 cycles
        for(int i = 0; i < 6; i++){
            cpu.tick();
        }

    }
    ~CPUFixture(){}

    void setImmediate(uint8_t opcode, uint8_t value){
        bus.memory[0x0000] = opcode;
        bus.memory[0x0001] = value;
    }

    void setAbsolute(uint8_t opcode, uint16_t valueAddress, uint8_t value){
        bus.memory[0x0000] = opcode;
        bus.memory[0x0001] = (valueAddress & 0x00FF);
        bus.memory[0x0002] = ((valueAddress & 0xFF00) >> 4);
        bus.memory[valueAddress] = value;
    }

    void setZeroPage(uint8_t opcode, uint8_t zeroPageAddress, uint8_t value){
        bus.memory[0x0000] = opcode;
        bus.memory[0x0001] = zeroPageAddress;
        bus.memory[0x0100 + zeroPageAddress] = value;
    }

    uint16_t setIndexedZeroPage(uint8_t opcode, uint8_t offset, uint8_t indexValue, uint8_t value){
        bus.memory[0x0000] = opcode;
        bus.memory[0x0001] = offset;
        uint16_t valueAddress = (0x0100 + offset + indexValue) % 0x0100;
        bus.memory[valueAddress] = value;
        return valueAddress;
    }

    uint16_t setIndexedAbsolute(uint8_t opcode, uint16_t address, uint8_t indexValue, uint8_t value){
        bus.memory[0x0000] = opcode;
        bus.memory[0x0001] = (address & 0x00FF);
        bus.memory[0x0002] = ((address & 0xFF00) >> 4);
        uint16_t valueAddress = address + indexValue;
        bus.memory[valueAddress] = value;
        return valueAddress;
    }

    uint16_t setRelative(uint8_t opcode, int8_t relative){
        bus.memory[0x0000] = opcode;
        bus.memory[0x0001] = relative;
        return (opcode + relative);
    }

    void execute(int cycles){
        for(int i = 0; i < cycles; i++){
            cpu.tick();
        }
    }

    // CPU
    V6502::CPU cpu;

    // Memory bus for testing
    MemoryBus bus;
};

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

/**
 * @brief Test BCC when carry is not set
 */
BOOST_FIXTURE_TEST_CASE(BCC_True, CPUFixture){
    // Set the relative address to 4 bytes ahead
    uint16_t nextPC = setRelative(0x90, 4);
    cpu.getRegisterFile().setCarry(false);
    execute(2);

    // Check that the program counter is equal to the new address
    BOOST_CHECK(cpu.getRegisterFile().programCounter == nextPC);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0002);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == nextPC);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0002);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == nextPC);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0002);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == nextPC);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0002);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == nextPC);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == nextPC);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0002);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == nextPC);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0002);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0002);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == nextPC);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0002);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == nextPC);
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
    BOOST_CHECK(cpu.getRegisterFile().programCounter == 0x0002);
}

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

BOOST_AUTO_TEST_SUITE_END()