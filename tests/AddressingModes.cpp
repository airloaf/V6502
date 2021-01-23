#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/AddressingModes.h"

#include "InstructionSet/Fixture.h"

namespace bdata = boost::unit_test::data;

using namespace V6502::AddressingModes;

BOOST_AUTO_TEST_SUITE(ADDRESSING_MODES);

BOOST_AUTO_TEST_CASE(ACCUMULATOR_TEST){
    V6502::RegisterFile rf;
    uint16_t decoded;
    BOOST_CHECK_EQUAL(accumulator(rf, nullptr, decoded, 0), true);
}

BOOST_AUTO_TEST_CASE(IMPLIED_TEST){
    V6502::RegisterFile rf;
    uint16_t decoded;
    BOOST_CHECK_EQUAL(implied(rf, nullptr, decoded, 0), true);
}

static auto IMM_PC = bdata::make({0x0000, 0x1234, 0xDEAD, 0xBEEF});
BOOST_DATA_TEST_CASE_F(Fixture, IMMEDIATE_TEST, IMM_PC, pc)
{
    rf.programCounter = pc;
    uint16_t decoded;

    BOOST_CHECK_EQUAL(implied(rf, bus, decoded, 0), true);
    BOOST_CHECK_EQUAL(decoded, pc+1);
}

static auto ABS_PC = bdata::make({0x0000, 0x1234, 0xDEAD, 0xBEEF});
static auto ABS_LOW = bdata::make({0xFF, 0xAD, 0xEF, 0x34});
static auto ABS_HIGH = bdata::make({0xFF, 0xDE, 0xBE, 0x12});
static auto ABS_DECODED = bdata::make({0xFFFF, 0xDEAD, 0xBEEF, 0x1234});
static auto ABS_DATA = ABS_PC ^ ABS_LOW ^ ABS_HIGH ^ ABS_DECODED;
BOOST_DATA_TEST_CASE_F(Fixture, ABSOLUTE_TEST, ABS_DATA, pc, low, high, expected)
{
    rf.programCounter = pc;
    bus->write(rf.programCounter, low);
    bus->write(rf.programCounter+1, high);
    uint16_t decoded;

    BOOST_CHECK_EQUAL(absolute(rf, bus, decoded, 0), false);
    BOOST_CHECK_EQUAL(absolute(rf, bus, decoded, 1), true);
    BOOST_CHECK_EQUAL(decoded, expected);

}

static auto ZP_PC = bdata::make({0xF000, 0x1234, 0xDEAD, 0xBEEF});
static auto ZP_INDEX = bdata::make({0x00, 0xFF, 0x4D, 0xD6});
static auto ZP_EXPECTED = bdata::make({0x0000, 0x00FF, 0x004D, 0x00D6});
static auto ZP_DATA = ZP_PC ^ ZP_INDEX ^ ZP_EXPECTED;
BOOST_DATA_TEST_CASE_F(Fixture, ZERO_PAGE_TEST, ZP_DATA, pc, index, expected)
{
    rf.programCounter = pc;
    bus->write(rf.programCounter, index);
    uint16_t decoded;

    BOOST_CHECK_EQUAL(absolute(rf, bus, decoded, 0), false);
    BOOST_CHECK_EQUAL(absolute(rf, bus, decoded, 1), true);
    BOOST_CHECK_EQUAL(decoded, expected);

}

BOOST_AUTO_TEST_SUITE_END()