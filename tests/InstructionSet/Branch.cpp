#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/InstructionSet/InstructionSet.h"

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

using namespace V6502::InstructionSet;

BOOST_AUTO_TEST_SUITE(BRANCH_INSTRUCTIONS)

static auto BCC_INITIAL_PC =    bdata::make({0x0100, 0x0200, 0x03F0, 0x0200});
static auto BCC_OFFSET =        bdata::make({0x10, 0x50, 0x20, 0xFA});
static auto BCC_AFTER_PC =      bdata::make({0x0100, 0x0250, 0x0410, 0x01FA});
static auto BCC_FLAG =          bdata::make({true, false,   false, false});
static auto BCC_NUM_CYCLES =    bdata::make({1,     2,      3, 3});
static auto BCC_DATA = BCC_INITIAL_PC ^ BCC_OFFSET ^ BCC_AFTER_PC ^ BCC_FLAG ^ BCC_NUM_CYCLES;
BOOST_DATA_TEST_CASE_F(Fixture, BCC_TEST, BCC_DATA, pc_before, offset, pc_after, flag, cycles)
{
    rf.programCounter = pc_before;
    rf.setCarry(flag);
    bus->write(pc_before-1, offset);

    for(int i = 0; i < cycles-1; i++){
        BOOST_CHECK_EQUAL(BCC(rf, bus, pc_before-1, i), false);
    }
    BOOST_CHECK_EQUAL(BCC(rf, bus, pc_before-1, cycles-1), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_after);
}

static auto BCS_INITIAL_PC =    bdata::make({0x0100, 0x0200, 0x03F0, 0x0200});
static auto BCS_OFFSET =        bdata::make({0x10, 0x50, 0x20, 0xFA});
static auto BCS_AFTER_PC =      bdata::make({0x0100, 0x0250, 0x0410, 0x01FA});
static auto BCS_FLAG =          bdata::make({false, true, true, true});
static auto BCS_NUM_CYCLES =    bdata::make({1,     2,      3, 3});
static auto BCS_DATA = BCS_INITIAL_PC ^ BCS_OFFSET ^ BCS_AFTER_PC ^ BCS_FLAG ^ BCS_NUM_CYCLES;
BOOST_DATA_TEST_CASE_F(Fixture, BCS_TEST, BCS_DATA, pc_before, offset, pc_after, flag, cycles)
{
    rf.programCounter = pc_before;
    rf.setCarry(flag);
    bus->write(pc_before-1, offset);

    for(int i = 0; i < cycles-1; i++){
        BOOST_CHECK_EQUAL(BCS(rf, bus, pc_before-1, i), false);
    }
    BOOST_CHECK_EQUAL(BCS(rf, bus, pc_before-1, cycles-1), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_after);
}

static auto BEQ_INITIAL_PC =    bdata::make({0x0100, 0x0200, 0x03F0, 0x200});
static auto BEQ_OFFSET =        bdata::make({0x10, 0x50, 0x20, 0xFA});
static auto BEQ_AFTER_PC =      bdata::make({0x0100, 0x0250, 0x0410, 0x01FA});
static auto BEQ_FLAG =          bdata::make({false, true, true, true});
static auto BEQ_NUM_CYCLES =    bdata::make({1,     2,      3, 3});
static auto BEQ_DATA = BEQ_INITIAL_PC ^ BEQ_OFFSET ^ BEQ_AFTER_PC ^ BEQ_FLAG ^ BEQ_NUM_CYCLES;
BOOST_DATA_TEST_CASE_F(Fixture, BEQ_TEST, BEQ_DATA, pc_before, offset, pc_after, flag, cycles)
{
    rf.programCounter = pc_before;
    rf.setZero(flag);
    bus->write(pc_before-1, offset);

    for(int i = 0; i < cycles-1; i++){
        BOOST_CHECK_EQUAL(BEQ(rf, bus, pc_before-1, i), false);
    }
    BOOST_CHECK_EQUAL(BEQ(rf, bus, pc_before-1, cycles-1), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_after);
}

static auto BNE_INITIAL_PC =    bdata::make({0x0100, 0x0200, 0x03F0, 0x0200});
static auto BNE_OFFSET =        bdata::make({0x10, 0x50, 0x20, 0xFA});
static auto BNE_AFTER_PC =      bdata::make({0x0100, 0x0250, 0x0410, 0x01FA});
static auto BNE_FLAG =          bdata::make({true, false, false, false});
static auto BNE_NUM_CYCLES =    bdata::make({1,     2,      3, 3});
static auto BNE_DATA = BNE_INITIAL_PC ^ BNE_OFFSET ^ BNE_AFTER_PC ^ BNE_FLAG ^ BNE_NUM_CYCLES;
BOOST_DATA_TEST_CASE_F(Fixture, BNE_TEST, BNE_DATA, pc_before, offset, pc_after, flag, cycles)
{
    rf.programCounter = pc_before;
    rf.setZero(flag);
    bus->write(pc_before-1, offset);

    for(int i = 0; i < cycles-1; i++){
        BOOST_CHECK_EQUAL(BNE(rf, bus, pc_before-1, i), false);
    }
    BOOST_CHECK_EQUAL(BNE(rf, bus, pc_before-1, cycles-1), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_after);
}

static auto BMI_INITIAL_PC =    bdata::make({0x0100, 0x0200, 0x03F0, 0x0200});
static auto BMI_OFFSET =        bdata::make({0x10, 0x50, 0x20, 0xFA});
static auto BMI_AFTER_PC =      bdata::make({0x0100, 0x0250, 0x0410, 0x01FA});
static auto BMI_FLAG =          bdata::make({false, true, true, true});
static auto BMI_NUM_CYCLES =    bdata::make({1,     2,      3, 3});
static auto BMI_DATA = BMI_INITIAL_PC ^ BMI_OFFSET ^ BMI_AFTER_PC ^ BMI_FLAG ^ BMI_NUM_CYCLES;
BOOST_DATA_TEST_CASE_F(Fixture, BMI_TEST, BMI_DATA, pc_before, offset, pc_after, flag, cycles)
{
    rf.programCounter = pc_before;
    rf.setNegative(flag);
    bus->write(pc_before-1, offset);

    for(int i = 0; i < cycles-1; i++){
        BOOST_CHECK_EQUAL(BMI(rf, bus, pc_before-1, i), false);
    }
    BOOST_CHECK_EQUAL(BMI(rf, bus, pc_before-1, cycles-1), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_after);
}

static auto BPL_INITIAL_PC =    bdata::make({0x0100, 0x0200, 0x03F0, 0x0200});
static auto BPL_OFFSET =        bdata::make({0x10, 0x50, 0x20, 0xFA});
static auto BPL_AFTER_PC =      bdata::make({0x0100, 0x0250, 0x0410, 0x01FA});
static auto BPL_FLAG =          bdata::make({true, false, false, false});
static auto BPL_NUM_CYCLES =    bdata::make({1,     2,      3, 3});
static auto BPL_DATA = BPL_INITIAL_PC ^ BPL_OFFSET ^ BPL_AFTER_PC ^ BPL_FLAG ^ BPL_NUM_CYCLES;
BOOST_DATA_TEST_CASE_F(Fixture, BPL_TEST, BPL_DATA, pc_before, offset, pc_after, flag, cycles)
{
    rf.programCounter = pc_before;
    rf.setNegative(flag);
    bus->write(pc_before-1, offset);

    for(int i = 0; i < cycles-1; i++){
        BOOST_CHECK_EQUAL(BPL(rf, bus, pc_before-1, i), false);
    }
    BOOST_CHECK_EQUAL(BPL(rf, bus, pc_before-1, cycles-1), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_after);
}

static auto BVC_INITIAL_PC =    bdata::make({0x0100, 0x0200, 0x03F0, 0x0200});
static auto BVC_OFFSET =        bdata::make({0x10, 0x50, 0x20, 0xFA});
static auto BVC_AFTER_PC =      bdata::make({0x0100, 0x0250, 0x0410, 0x01FA});
static auto BVC_FLAG =          bdata::make({true, false, false, false});
static auto BVC_NUM_CYCLES =    bdata::make({1,     2,      3, 3});
static auto BVC_DATA = BVC_INITIAL_PC ^ BVC_OFFSET ^ BVC_AFTER_PC ^ BVC_FLAG ^ BVC_NUM_CYCLES;
BOOST_DATA_TEST_CASE_F(Fixture, BVC_TEST, BVC_DATA, pc_before, offset, pc_after, flag, cycles)
{
    rf.programCounter = pc_before;
    rf.setOverflow(flag);
    bus->write(pc_before-1, offset);

    for(int i = 0; i < cycles-1; i++){
        BOOST_CHECK_EQUAL(BVC(rf, bus, pc_before-1, i), false);
    }
    BOOST_CHECK_EQUAL(BVC(rf, bus, pc_before-1, cycles-1), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_after);
}

static auto BVS_INITIAL_PC =    bdata::make({0x0100, 0x0200, 0x03F0, 0x0200});
static auto BVS_OFFSET =        bdata::make({0x10, 0x50, 0x20, 0xFA});
static auto BVS_AFTER_PC =      bdata::make({0x0100, 0x0250, 0x0410, 0x01FA});
static auto BVS_FLAG =          bdata::make({false, true, true, true});
static auto BVS_NUM_CYCLES =    bdata::make({1,     2,      3, 3});
static auto BVS_DATA = BVS_INITIAL_PC ^ BVS_OFFSET ^ BVS_AFTER_PC ^ BVS_FLAG ^ BVS_NUM_CYCLES;
BOOST_DATA_TEST_CASE_F(Fixture, BVS_TEST, BVS_DATA, pc_before, offset, pc_after, flag, cycles)
{
    rf.programCounter = pc_before;
    rf.setOverflow(flag);
    bus->write(pc_before-1, offset);

    for(int i = 0; i < cycles-1; i++){
        BOOST_CHECK_EQUAL(BVS(rf, bus, pc_before-1, i), false);
    }
    BOOST_CHECK_EQUAL(BVS(rf, bus, pc_before-1, cycles-1), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_after);
}

BOOST_AUTO_TEST_SUITE_END()