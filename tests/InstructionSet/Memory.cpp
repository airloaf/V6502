#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/InstructionSet.h"

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

using namespace V6502::InstructionSet;

BOOST_AUTO_TEST_SUITE(MEMORY_INSTRUCTIONS)

static auto LDA_VALUE = bdata::make({0x00, 0xFF, 0x7F, 0x80});
static auto LDA_Z_FLAG = bdata::make({true, false, false, false});
static auto LDA_N_FLAG = bdata::make({false, true, false, true});
static auto LDA_ADDR = bdata::make({0x0000, 0x1234, 0xCDCD, 0xBEEF});
static auto LDA_DATA = LDA_VALUE ^ LDA_Z_FLAG ^ LDA_N_FLAG ^ LDA_ADDR;
BOOST_DATA_TEST_CASE_F(Fixture, LDA_TEST, LDA_DATA, v, z, n, addr)
{
    bus->write(addr, v);

    LDA(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(rf.accumulator, v);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto LDX_VALUE = bdata::make({0x00, 0xFF, 0x7F, 0x80});
static auto LDX_Z_FLAG = bdata::make({true, false, false, false});
static auto LDX_N_FLAG = bdata::make({false, true, false, true});
static auto LDX_ADDR = bdata::make({0x0000, 0x1234, 0xCDCD, 0xBEEF});
static auto LDX_DATA = LDX_VALUE ^ LDX_Z_FLAG ^ LDX_N_FLAG ^ LDX_ADDR;
BOOST_DATA_TEST_CASE_F(Fixture, LDX_TEST, LDX_DATA, v, z, n, addr)
{
    bus->write(addr, v);

    LDX(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(rf.accumulator, v);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto LDY_VALUE = bdata::make({0x00, 0xFF, 0x7F, 0x80});
static auto LDY_Z_FLAG = bdata::make({true, false, false, false});
static auto LDY_N_FLAG = bdata::make({false, true, false, true});
static auto LDY_ADDR = bdata::make({0x0000, 0x1234, 0xCDCD, 0xBEEF});
static auto LDY_DATA = LDY_VALUE ^ LDY_Z_FLAG ^ LDY_N_FLAG ^ LDY_ADDR;
BOOST_DATA_TEST_CASE_F(Fixture, LDY_TEST, LDY_DATA, v, z, n, addr)
{
    bus->write(addr, v);

    LDY(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(rf.accumulator, v);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto STA_VALUE = bdata::make({0x00, 0x12, 0xCE, 0xFE});
static auto STA_ADDR = bdata::make({0x0000, 0xFFFF, 0xDEAD, 0xBEEF});
static auto STA_DATA = STA_VALUE ^ STA_ADDR;
BOOST_DATA_TEST_CASE_F(Fixture, STA_TEST, STA_DATA, v, addr)
{
    rf.accumulator = v;

    STA(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(bus->read(addr), v);
}

static auto STX_VALUE = bdata::make({0x00, 0x12, 0xCE, 0xFE});
static auto STX_ADDR = bdata::make({0x0000, 0xFFFF, 0xDEAD, 0xBEEF});
static auto STX_DATA = STX_VALUE ^ STX_ADDR;
BOOST_DATA_TEST_CASE_F(Fixture, STX_TEST, STX_DATA, v, addr)
{
    rf.accumulator = v;

    STX(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(bus->read(addr), v);
}

static auto STY_VALUE = bdata::make({0x00, 0x12, 0xCE, 0xFE});
static auto STY_ADDR = bdata::make({0x0000, 0xFFFF, 0xDEAD, 0xBEEF});
static auto STY_DATA = STY_VALUE ^ STY_ADDR;
BOOST_DATA_TEST_CASE_F(Fixture, STY_TEST, STY_DATA, v, addr)
{
    rf.accumulator = v;

    STY(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(bus->read(addr), v);
}

BOOST_AUTO_TEST_SUITE_END()