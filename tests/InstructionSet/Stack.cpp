#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/InstructionSet/InstructionSet.h"

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

using namespace V6502::InstructionSet;

BOOST_AUTO_TEST_SUITE(STACK_INSTRUCTIONS)

static auto PHA_VALUE = bdata::make({0x00, 0x12, 0xFF});
static auto PHA_STACK = bdata::make({0x00, 0xFF, 0x77});
static auto PHA_S_AFT = bdata::make({0xFF, 0xFE, 0x76});
static auto PHA_ADDR = bdata::make({0x100, 0x1FF, 0x177});
static auto PHA_DATA = PHA_VALUE ^ PHA_STACK ^ PHA_S_AFT ^ PHA_ADDR;
BOOST_DATA_TEST_CASE_F(Fixture, PHA_TEST, PHA_DATA, v, sp, sp_after, addr)
{
    rf.accumulator = v;
    rf.stackPointer = sp;

    PHA(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(bus->read(addr), v);
    BOOST_CHECK_EQUAL(rf.stackPointer, sp_after);
}

static auto PHP_VALUE = bdata::make({0x00, 0x12, 0xFF});
static auto PHP_STACK = bdata::make({0x00, 0xFF, 0x77});
static auto PHP_S_AFT = bdata::make({0xFF, 0xFE, 0x76});
static auto PHP_ADDR = bdata::make({0x100, 0x1FF, 0x177});
static auto PHP_DATA = PHP_VALUE ^ PHP_STACK ^ PHP_S_AFT ^ PHP_ADDR;
BOOST_DATA_TEST_CASE_F(Fixture, PHP_TEST, PHP_DATA, v, sp, sp_after, addr)
{
    rf.status = v;
    rf.stackPointer = sp;

    PHP(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(bus->read(addr), v);
    BOOST_CHECK_EQUAL(rf.stackPointer, sp_after);
}

static auto PLA_VALUE = bdata::make({0x00, 0x12, 0xFF});
static auto PLA_STACK = bdata::make({0x00, 0xFF, 0x77});
static auto PLA_S_AFT = bdata::make({0x01, 0x00, 0x78});
static auto PLA_ADDR = bdata::make({0x101, 0x100, 0x178});
static auto PLA_N = bdata::make({false, false, true});
static auto PLA_Z = bdata::make({true, false, false});
static auto PLA_DATA = PLA_VALUE ^ PLA_STACK ^ PLA_S_AFT ^ PLA_ADDR ^ PLA_N ^ PLA_Z;
BOOST_DATA_TEST_CASE_F(Fixture, PLA_TEST, PLA_DATA, v, sp, sp_after, addr, n, z)
{
    bus->write(addr, v);
    rf.stackPointer = sp;

    PLA(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.accumulator, v);
    BOOST_CHECK_EQUAL(rf.stackPointer, sp_after);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
}

static auto PLP_VALUE = bdata::make({0x00, 0x12, 0xDF});
static auto PLP_VALUE_AFT = bdata::make({0x20, 0x32, 0xFF});
static auto PLP_STACK = bdata::make({0x00, 0xFF, 0x77});
static auto PLP_S_AFT = bdata::make({0x01, 0x00, 0x78});
static auto PLP_ADDR = bdata::make({0x101, 0x100, 0x178});
static auto PLP_DATA = PLP_VALUE ^ PLP_VALUE_AFT ^ PLP_STACK ^ PLP_S_AFT ^ PLP_ADDR;
BOOST_DATA_TEST_CASE_F(Fixture, PLP_TEST, PLP_DATA, v, v_aft, sp, sp_after, addr)
{
    bus->write(addr, v);
    rf.stackPointer = sp;

    PLP(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.status, v_aft);
    BOOST_CHECK_EQUAL(rf.stackPointer, sp_after);
}

BOOST_AUTO_TEST_SUITE_END()