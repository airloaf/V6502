#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/InstructionSet.h"

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

using namespace V6502::InstructionSet;

BOOST_AUTO_TEST_SUITE(MEMORY_INSTRUCTIONS)

static auto DEC_VALUE = bdata::make({0x00, 0xFF, 0x01, 0x80});
static auto DEC_ADDR = bdata::make({0x0000, 0xFFFF, 0x1234, 0xBEEF});
static auto DEC_RES = bdata::make({0xFF, 0xFE, 0x00, 0x7F});
static auto DEC_Z_FLAG = bdata::make({false, false, true, false});
static auto DEC_N_FLAG = bdata::make({true, true, false, false});
static auto DEC_DATA = DEC_VALUE ^ DEC_ADDR ^ DEC_RES ^ DEC_Z_FLAG ^ DEC_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, DEC_TEST, DEC_DATA, v, addr, res, z, n)
{
    bus->write(addr, v);

    DEC(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(bus->read(addr), res);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto DEX_VALUE = bdata::make({0x00, 0xFF, 0x01, 0x80});
static auto DEX_RES = bdata::make({0xFF, 0xFE, 0x00, 0x7F});
static auto DEX_Z_FLAG = bdata::make({false, false, true, false});
static auto DEX_N_FLAG = bdata::make({true, true, false, false});
static auto DEX_DATA = DEX_VALUE ^ DEX_RES ^ DEX_Z_FLAG ^ DEX_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, DEX_TEST, DEX_DATA, v, res, z, n)
{
    rf.indexX = v;

    DEX(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.indexX, res);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto DEY_VALUE = bdata::make({0x00, 0xFF, 0x01, 0x80});
static auto DEY_RES = bdata::make({0xFF, 0xFE, 0x00, 0x7F});
static auto DEY_Z_FLAG = bdata::make({false, false, true, false});
static auto DEY_N_FLAG = bdata::make({true, true, false, false});
static auto DEY_DATA = DEY_VALUE ^ DEY_RES ^ DEY_Z_FLAG ^ DEY_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, DEY_TEST, DEY_DATA, v, res, z, n)
{
    rf.indexY = v;

    DEY(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.indexY, res);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto INC_VALUE = bdata::make({0x00, 0xFF, 0x01, 0x7F});
static auto INC_ADDR = bdata::make({0x0000, 0xFFFF, 0x1234, 0xBEEF});
static auto INC_RES = bdata::make({0x01, 0x00, 0x02, 0x80});
static auto INC_Z_FLAG = bdata::make({false, true, false, false});
static auto INC_N_FLAG = bdata::make({false, false, false, true});
static auto INC_DATA = INC_VALUE ^ INC_ADDR ^ INC_RES ^ INC_Z_FLAG ^ INC_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, INC_TEST, INC_DATA, v, addr, res, z, n)
{
    bus->write(addr, v);

    INC(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(bus->read(addr), res);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto INX_VALUE = bdata::make({0x00, 0xFF, 0x01, 0x7F});
static auto INX_RES = bdata::make({0x01, 0x00, 0x02, 0x80});
static auto INX_Z_FLAG = bdata::make({false, true, false, false});
static auto INX_N_FLAG = bdata::make({false, false, false, true});
static auto INX_DATA = INX_VALUE ^ INX_RES ^ INX_Z_FLAG ^ INX_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, INX_TEST, INX_DATA, v, res, z, n)
{
    rf.indexX = v;

    INX(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.indexX, res);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto INY_VALUE = bdata::make({0x00, 0xFF, 0x01, 0x7F});
static auto INY_RES = bdata::make({0x01, 0x00, 0x02, 0x80});
static auto INY_Z_FLAG = bdata::make({false, true, false, false});
static auto INY_N_FLAG = bdata::make({false, false, false, true});
static auto INY_DATA = INY_VALUE ^ INY_RES ^ INY_Z_FLAG ^ INY_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, INY_TEST, INY_DATA, v, res, z, n)
{
    rf.indexY = v;

    INY(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.indexY, res);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

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