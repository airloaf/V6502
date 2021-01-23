#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/InstructionSet/InstructionSet.h"

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

using namespace V6502::InstructionSet;

BOOST_AUTO_TEST_SUITE(STATUS_INSTRUCTIONS)

static auto BIT_ACCUM = bdata::make({0x00, 0x1, 0x23, 0xB1, 0x88});
static auto BIT_MEM = bdata::make({0x00, 0xFF, 0x23, 0xB2, 0x77});
static auto BIT_ADDR = bdata::make({0x0000, 0xDEAD, 0xBEEF, 0x1234, 0x5432});
static auto BIT_Z_FLAG = bdata::make({true, false, true, false, false});
static auto BIT_V_FLAG = bdata::make({false, true, false, false, true});
static auto BIT_N_FLAG = bdata::make({false, true, false, true, false});
static auto BIT_DATA = BIT_ACCUM ^ BIT_MEM ^ BIT_ADDR ^ BIT_Z_FLAG ^ BIT_V_FLAG ^ BIT_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, BIT_TEST, BIT_DATA, a, m, addr, z, v, n)
{
    rf.accumulator = a;
    bus->write(addr, m);

    BIT(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getOverflow(), v);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto CLC_FLAG = bdata::make({false, true});
BOOST_DATA_TEST_CASE_F(Fixture, CLC_TEST, CLC_FLAG, f)
{
    rf.setCarry(f);

    CLC(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.getCarry(), false);
}

static auto CLD_FLAG = bdata::make({false, true});
BOOST_DATA_TEST_CASE_F(Fixture, CLD_TEST, CLD_FLAG, f)
{
    rf.setDecimalMode(f);

    CLD(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.getDecimalMode(), false);
}

static auto CLI_FLAG = bdata::make({false, true});
BOOST_DATA_TEST_CASE_F(Fixture, CLI_TEST, CLI_FLAG, f)
{
    rf.setIRQDisable(f);

    CLI(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.getIRQDisable(), false);
}

static auto CLV_FLAG = bdata::make({false, true});
BOOST_DATA_TEST_CASE_F(Fixture, CLV_TEST, CLV_FLAG, f)
{
    rf.setOverflow(f);

    CLV(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.getOverflow(), false);
}

// The CMP, CPX and CPY instruction is quite complex.
// This article will answer any questions regarding how the flags are computed.
// http://www.6502.org/tutorials/compare_beyond.html

static auto CMP_RVALUE = bdata::make({0x00, 0x1, 0x32, 0x23, 0x77});
static auto CMP_MVALUE = bdata::make({0x00, 0xFF, 0x23, 0x32, 0x77});
static auto CMP_ADDR = bdata::make({0x0000, 0xDEAD, 0xBEEF, 0x1234, 0x5432});
static auto CMP_C_FLAG = bdata::make({true, false, true, false, true});
static auto CMP_Z_FLAG = bdata::make({true, false, false, false, true});
static auto CMP_N_FLAG = bdata::make({false, false, false, true, false});
static auto CMP_DATA = CMP_RVALUE ^ CMP_MVALUE ^ CMP_ADDR ^ CMP_C_FLAG ^ CMP_Z_FLAG ^ CMP_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, CMP_TEST, CMP_DATA, r, m, addr, c, z, n)
{
    rf.accumulator = r;
    bus->write(addr, m);

    CMP(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(rf.getCarry(), c);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto CPX_RVALUE = bdata::make({0x00, 0x1, 0x32, 0x23, 0x77});
static auto CPX_MVALUE = bdata::make({0x00, 0xFF, 0x23, 0x32, 0x77});
static auto CPX_ADDR = bdata::make({0x0000, 0xDEAD, 0xBEEF, 0x1234, 0x5432});
static auto CPX_C_FLAG = bdata::make({true, false, true, false, true});
static auto CPX_Z_FLAG = bdata::make({true, false, false, false, true});
static auto CPX_N_FLAG = bdata::make({false, false, false, true, false});
static auto CPX_DATA = CPX_RVALUE ^ CPX_MVALUE ^ CPX_ADDR ^ CPX_C_FLAG ^ CPX_Z_FLAG ^ CPX_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, CPX_TEST, CPX_DATA, r, m, addr, c, z, n)
{
    rf.indexX = r;
    bus->write(addr, m);

    CPX(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(rf.getCarry(), c);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto CPY_RVALUE = bdata::make({0x00, 0x1, 0x32, 0x23, 0x77});
static auto CPY_MVALUE = bdata::make({0x00, 0xFF, 0x23, 0x32, 0x77});
static auto CPY_ADDR = bdata::make({0x0000, 0xDEAD, 0xBEEF, 0x1234, 0x5432});
static auto CPY_C_FLAG = bdata::make({true, false, true, false, true});
static auto CPY_Z_FLAG = bdata::make({true, false, false, false, true});
static auto CPY_N_FLAG = bdata::make({false, false, false, true, false});
static auto CPY_DATA = CPY_RVALUE ^ CPY_MVALUE ^ CPY_ADDR ^ CPY_C_FLAG ^ CPY_Z_FLAG ^ CPY_N_FLAG;
BOOST_DATA_TEST_CASE_F(Fixture, CPY_TEST, CPY_DATA, r, m, addr, c, z, n)
{
    rf.indexY = r;
    bus->write(addr, m);

    CPY(rf, bus, addr, 0);

    BOOST_CHECK_EQUAL(rf.getCarry(), c);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
}

static auto SEC_FLAG = bdata::make({false, true});
BOOST_DATA_TEST_CASE_F(Fixture, SEC_TEST, SEC_FLAG, f)
{
    rf.setCarry(f);

    SEC(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.getCarry(), true);
}

static auto SED_FLAG = bdata::make({false, true});
BOOST_DATA_TEST_CASE_F(Fixture, SED_TEST, SED_FLAG, f)
{
    rf.setDecimalMode(f);

    SED(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.getDecimalMode(), true);
}

static auto SEI_FLAG = bdata::make({false, true});
BOOST_DATA_TEST_CASE_F(Fixture, SEI_TEST, SEI_FLAG, f)
{
    rf.setIRQDisable(f);

    SEI(rf, bus, 0, 0);

    BOOST_CHECK_EQUAL(rf.getIRQDisable(), true);
}

BOOST_AUTO_TEST_SUITE_END()