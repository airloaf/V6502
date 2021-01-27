#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/InstructionSet/InstructionSet.h"

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

using namespace V6502::InstructionSet;

BOOST_AUTO_TEST_SUITE(SYSTEM_INSTRUCTIONS)

static auto BRK_PC_BEFORE = bdata::make({0x0002, 0xDEAD, 0xBEEF});
static auto BRK_PC_STATUS = bdata::make({0x02, 0xAD, 0xEF});
static auto BRK_PC_STATUS_AFT = bdata::make({0x12, 0xBD, 0xFF});
static auto BRK_PC_B_LOW  = bdata::make({0x03, 0xAE, 0xF0});
static auto BRK_PC_B_HIGH = bdata::make({0x00, 0xDE, 0xBE});
static auto BRK_PC_AFTER = bdata::make({0x1234, 0x7777, 0xBADD});
static auto BRK_DATA = BRK_PC_BEFORE ^ BRK_PC_STATUS ^ BRK_PC_STATUS_AFT ^ BRK_PC_B_HIGH ^ BRK_PC_B_LOW ^ BRK_PC_AFTER;
BOOST_DATA_TEST_CASE_F(Fixture, BRK_TEST, BRK_DATA, pc_b, status, status_aft, high, low, pc_a)
{
    rf.stackPointer = 0xFF;
    rf.programCounter = pc_b;
    rf.status = status;

    bus->write(0xFFFE, pc_a & 0x00FF);
    bus->write(0xFFFF, (pc_a & 0xFF00) >> 8);

    uint16_t statusPtr = 0x1FD;
    uint16_t lowPtr = 0x1FE;
    uint16_t highPtr = 0x1FF;

    BOOST_CHECK_EQUAL(BRK(rf, bus, pc_a, 0), false);
    BOOST_CHECK_EQUAL(BRK(rf, bus, pc_a, 1), false);
    BOOST_CHECK_EQUAL(BRK(rf, bus, pc_a, 2), false);
    BOOST_CHECK_EQUAL(BRK(rf, bus, pc_a, 3), false);
    BOOST_CHECK_EQUAL(BRK(rf, bus, pc_a, 4), true);

    BOOST_CHECK_EQUAL(rf.programCounter, pc_a);
    BOOST_CHECK_EQUAL(bus->read(statusPtr), status_aft);
    BOOST_CHECK_EQUAL(bus->read(lowPtr), low);
    BOOST_CHECK_EQUAL(bus->read(highPtr), high);
    BOOST_CHECK_EQUAL(rf.status, status | 0x14);
}

static auto JMP_PC_BEFORE = bdata::make({0x0000, 0xDEAD, 0xBEEF});
static auto JMP_PC_AFTER = bdata::make({0x1234, 0x7777, 0xBADD});
static auto JMP_DATA = JMP_PC_BEFORE ^ JMP_PC_AFTER;
BOOST_DATA_TEST_CASE_F(Fixture, JMP_TEST, JMP_DATA, pc_b, pc_a)
{
    rf.programCounter = pc_b;
    BOOST_CHECK_EQUAL(JMP(rf, bus, pc_a, 0), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_a);
}

static auto JSR_PC_BEFORE = bdata::make({0x0002, 0xDEAD, 0xBEEF});
static auto JSR_PC_B_LOW  = bdata::make({0x01, 0xAC, 0xEE});
static auto JSR_PC_B_HIGH = bdata::make({0x00, 0xDE, 0xBE});
static auto JSR_PC_AFTER = bdata::make({0x1234, 0x7777, 0xBADD});
static auto JSR_DATA = JSR_PC_BEFORE ^ JSR_PC_B_HIGH ^ JSR_PC_B_LOW ^ JSR_PC_AFTER;
BOOST_DATA_TEST_CASE_F(Fixture, JSR_TEST, JSR_DATA, pc_b, high, low, pc_a)
{
    rf.stackPointer = 0xFF;
    rf.programCounter = pc_b;

    uint16_t lowPtr = 0x1FE;
    uint16_t highPtr = 0x1FF;

    BOOST_CHECK_EQUAL(JSR(rf, bus, pc_a, 0), false);
    BOOST_CHECK_EQUAL(JSR(rf, bus, pc_a, 1), true);
    BOOST_CHECK_EQUAL(rf.programCounter, pc_a);
    BOOST_CHECK_EQUAL(bus->read(lowPtr), low);
    BOOST_CHECK_EQUAL(bus->read(highPtr), high);
}

static auto RTI_PC_BEFORE = bdata::make({0x0002, 0xDEAD, 0xBEEF});
static auto RTI_PC_STATUS = bdata::make({0x77, 0x54, 0x44});
static auto RTI_PC_A_LOW  = bdata::make({0x34, 0x77, 0xDD});
static auto RTI_PC_A_HIGH = bdata::make({0x12, 0x77, 0xBA});
static auto RTI_PC_AFTER = bdata::make({0x1234, 0x7777, 0xBADD});
static auto RTI_DATA = RTI_PC_BEFORE ^ RTI_PC_STATUS ^ RTI_PC_A_HIGH ^ RTI_PC_A_LOW ^ RTI_PC_AFTER;
BOOST_DATA_TEST_CASE_F(Fixture, RTI_TEST, RTI_DATA, pc_b, status, high, low, pc_a)
{
    rf.stackPointer = 0xFC;
    rf.programCounter = pc_b;

    uint16_t statusPtr = 0x1FD;
    uint16_t lowPtr = 0x1FE;
    uint16_t highPtr = 0x1FF;

    bus->write(statusPtr, status);
    bus->write(lowPtr, low);
    bus->write(highPtr, high);

    BOOST_CHECK_EQUAL(RTI(rf, bus, 0, 0), false);
    BOOST_CHECK_EQUAL(RTI(rf, bus, 0, 1), false);
    BOOST_CHECK_EQUAL(RTI(rf, bus, 0, 2), false);
    BOOST_CHECK_EQUAL(RTI(rf, bus, 0, 3), true);

    BOOST_CHECK_EQUAL(rf.programCounter, pc_a);
}

static auto RTS_PC_BEFORE = bdata::make({0x0002, 0xDEAD, 0xBEEF});
static auto RTS_PC_A_LOW  = bdata::make({0x33, 0x76, 0xDC});
static auto RTS_PC_A_HIGH = bdata::make({0x12, 0x77, 0xBA});
static auto RTS_PC_AFTER = bdata::make({0x1234, 0x7777, 0xBADD});
static auto RTS_DATA = RTS_PC_BEFORE ^ RTS_PC_A_HIGH ^ RTS_PC_A_LOW ^ RTS_PC_AFTER;
BOOST_DATA_TEST_CASE_F(Fixture, RTS_TEST, RTS_DATA, pc_b, high, low, pc_a)
{
    rf.stackPointer = 0xFD;
    rf.programCounter = pc_b;

    uint16_t lowPtr = 0x1FE;
    uint16_t highPtr = 0x1FF;

    bus->write(lowPtr, low);
    bus->write(highPtr, high);

    BOOST_CHECK_EQUAL(RTS(rf, bus, 0, 0), false);
    BOOST_CHECK_EQUAL(RTS(rf, bus, 0, 1), false);
    BOOST_CHECK_EQUAL(RTS(rf, bus, 0, 2), false);
    BOOST_CHECK_EQUAL(RTS(rf, bus, 0, 3), true);

    BOOST_CHECK_EQUAL(rf.programCounter, pc_a);
}

BOOST_AUTO_TEST_SUITE_END()