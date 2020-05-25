#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "Fixture.h"

namespace bdata = boost::unit_test::data;
using namespace V6502;

BOOST_AUTO_TEST_SUITE(REGISTER_INSTRUCTIONS);

// Data to use for the test
static auto DEX_IndexBefore =          bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto DEX_IndexAfter =           bdata::make({0xFF, 0x00, 0xFE, 0x3F});
static auto DEX_Negative =             bdata::make({true, false, false, false});
static auto DEX_Zero =                 bdata::make({false, true, false, false});
static auto DEX_DATA = DEX_IndexBefore ^ DEX_IndexAfter ^ DEX_Negative ^ DEX_Zero;

BOOST_DATA_TEST_CASE_F(CPUFixture, DEX, DEX_DATA, before, after, n, z){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexX = before;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().indexX == after);
    BOOST_CHECK(cpu.getRegisterFile().getNegative() == n);
    BOOST_CHECK(cpu.getRegisterFile().getZero() == z);
}

// Data to use for the test
static auto DEY_IndexBefore =          bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto DEY_IndexAfter =           bdata::make({0xFF, 0x00, 0xFE, 0x3F});
static auto DEY_Negative =             bdata::make({true, false, false, false});
static auto DEY_Zero =                 bdata::make({false, true, false, false});
static auto DEY_DATA = DEY_IndexBefore ^ DEY_IndexAfter ^ DEY_Negative ^ DEY_Zero;

BOOST_DATA_TEST_CASE_F(CPUFixture, DEY, DEY_DATA, before, after, n, z){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexY = before;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().indexY == after);
    BOOST_CHECK(cpu.getRegisterFile().getNegative() == n);
    BOOST_CHECK(cpu.getRegisterFile().getZero() == z);
}

// Data to use for the test
static auto INX_IndexBefore =          bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto INX_IndexAfter =           bdata::make({0x01, 0x02, 0x00, 0x41});
static auto INX_Negative =             bdata::make({false, false, false, false});
static auto INX_Zero =                 bdata::make({false, false, true, false});
static auto INX_DATA = INX_IndexBefore ^ INX_IndexAfter ^ INX_Negative ^ INX_Zero;

BOOST_DATA_TEST_CASE_F(CPUFixture, INX, INX_DATA, before, after, n, z){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexX = before;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().indexX == after);
    BOOST_CHECK(cpu.getRegisterFile().getNegative() == n);
    BOOST_CHECK(cpu.getRegisterFile().getZero() == z);
}

// Data to use for the test
static auto INY_IndexBefore =          bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto INY_IndexAfter =           bdata::make({0x01, 0x02, 0x00, 0x41});
static auto INY_Negative =             bdata::make({false, false, false, false});
static auto INY_Zero =                 bdata::make({false, false, true, false});
static auto INY_DATA = INY_IndexBefore ^ INY_IndexAfter ^ INY_Negative ^ INY_Zero;

BOOST_DATA_TEST_CASE_F(CPUFixture, INY, INY_DATA, before, after, n, z){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexY = before;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().indexY == after);
    BOOST_CHECK(cpu.getRegisterFile().getNegative() == n);
    BOOST_CHECK(cpu.getRegisterFile().getZero() == z);
}

// Data to use for the test
static auto TAX_IndexBefore =          bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto TAX_IndexAfter =           bdata::make({0x00, 0x77, 0x4F, 0xC9});
static auto TAX_Accumulator =          bdata::make({0x00, 0x77, 0x4F, 0xC9});
static auto TAX_DATA = TAX_IndexBefore ^ TAX_IndexAfter ^ TAX_Accumulator;

BOOST_DATA_TEST_CASE_F(CPUFixture, TAX, TAX_DATA, before, after, accumulator){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexX = before; rf.accumulator = accumulator;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().indexX == after);
}

// Data to use for the test
static auto TAY_IndexBefore =          bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto TAY_IndexAfter =           bdata::make({0x00, 0x77, 0x4F, 0xC9});
static auto TAY_Accumulator =          bdata::make({0x00, 0x77, 0x4F, 0xC9});
static auto TAY_DATA = TAY_IndexBefore ^ TAY_IndexAfter ^ TAY_Accumulator;

BOOST_DATA_TEST_CASE_F(CPUFixture, TAY, TAY_DATA, before, after, accumulator){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexY = before; rf.accumulator = accumulator;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().indexY == after);
}

// Data to use for the test
static auto TSX_IndexBefore =          bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto TSX_IndexAfter =           bdata::make({0x00, 0x77, 0x4F, 0xC9});
static auto TSX_StackPointer =         bdata::make({0x00, 0x77, 0x4F, 0xC9});
static auto TSX_DATA = TSX_IndexBefore ^ TSX_IndexAfter ^ TSX_StackPointer;

BOOST_DATA_TEST_CASE_F(CPUFixture, TSX, TSX_DATA, before, after, stackPointer){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexX = before; rf.stackPointer = stackPointer;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().indexX == after);
}

// Data to use for the test
static auto TXA_Index =                bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto TXA_Accumulator =          bdata::make({0x00, 0x77, 0x4F, 0xC9});
static auto TXA_DATA = TXA_Index ^ TXA_Accumulator;

BOOST_DATA_TEST_CASE_F(CPUFixture, TXA, TXA_DATA, index, accumulator){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexX = index; rf.accumulator = accumulator;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().accumulator == index);
}

// Data to use for the test
static auto TYA_Index =                bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto TYA_Accumulator =          bdata::make({0x00, 0x77, 0x4F, 0xC9});
static auto TYA_DATA = TYA_Index ^ TYA_Accumulator;

BOOST_DATA_TEST_CASE_F(CPUFixture, TYA, TYA_DATA, index, accumulator){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexY = index; rf.accumulator = accumulator;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().accumulator == index);
}

// Data to use for the test
static auto TXS_Index =                 bdata::make({0x00, 0x01, 0xFF, 0x40});
static auto TXS_StackPointer =          bdata::make({0x00, 0x77, 0x4F, 0xC9});
static auto TXS_DATA = TXS_Index ^ TXS_StackPointer;

BOOST_DATA_TEST_CASE_F(CPUFixture, TXS, TXS_DATA, index, stackPointer){
    bus.memory[0x0000] = 0xCA;
    RegisterFile rf; rf.indexY = index; rf.stackPointer = stackPointer;
    execute(2);
    BOOST_CHECK(cpu.getRegisterFile().stackPointer == index);
}

BOOST_AUTO_TEST_SUITE_END()