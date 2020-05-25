#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>

#include "MemoryBus.h"
#include "Instructions/Fixture.h"

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