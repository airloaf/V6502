#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/InstructionSet/InstructionSet.h"

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

using namespace V6502::InstructionSet;

BOOST_AUTO_TEST_SUITE(ARITHMETIC_INSTRUCTIONS)

static auto AND_V = bdata::make({0x00, 0xFF, 0x43});
static auto AND_ACCUM = bdata::make({0xFF, 0x80, 0xDB});
static auto AND_RESULT = bdata::make({0x00, 0x80, 0x43});
static auto AND_N = bdata::make({false, true, false});
static auto AND_Z = bdata::make({true, false, false});
static auto AND_DATA = AND_V ^ AND_ACCUM ^ AND_RESULT ^ AND_N ^ AND_Z;
BOOST_DATA_TEST_CASE_F(Fixture, AND_TEST, AND_DATA, v, accum, result, n, z)
{
    rf.accumulator = accum;
    bus->write(0x0000, v);

    BOOST_CHECK_EQUAL(AND(rf, bus, 0x0000, 0), true);
    BOOST_CHECK_EQUAL(rf.accumulator, result);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
}

static auto EOR_V = bdata::make({0x00, 0xFF, 0x43});
static auto EOR_ACCUM = bdata::make({0xFF, 0x80, 0x43});
static auto EOR_RESULT = bdata::make({0xFF, 0x7F, 0x00});
static auto EOR_N = bdata::make({true, false, false});
static auto EOR_Z = bdata::make({false, false, true});
static auto EOR_DATA = EOR_V ^ EOR_ACCUM ^ EOR_RESULT ^ EOR_N ^ EOR_Z;
BOOST_DATA_TEST_CASE_F(Fixture, EOR_TEST, EOR_DATA, v, accum, result, n, z)
{
    rf.accumulator = accum;
    bus->write(0x0000, v);

    BOOST_CHECK_EQUAL(EOR(rf, bus, 0x0000, 0), true);
    BOOST_CHECK_EQUAL(rf.accumulator, result);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
}

static auto ORA_V = bdata::make({0x00, 0x00, 0x43});
static auto ORA_ACCUM = bdata::make({0xFF, 0x00, 0xDB});
static auto ORA_RESULT = bdata::make({0xFF, 0x00, 0xDB});
static auto ORA_N = bdata::make({true, false, true});
static auto ORA_Z = bdata::make({false, true, false});
static auto ORA_DATA = ORA_V ^ ORA_ACCUM ^ ORA_RESULT ^ ORA_N ^ ORA_Z;
BOOST_DATA_TEST_CASE_F(Fixture, ORA_TEST, ORA_DATA, v, accum, result, n, z)
{
    rf.accumulator = accum;
    bus->write(0x0000, v);

    BOOST_CHECK_EQUAL(ORA(rf, bus, 0x0000, 0), true);
    BOOST_CHECK_EQUAL(rf.accumulator, result);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
}

static auto ASL_V = bdata::make({0x00, 0xFF, 0x4F, 0x80});
static auto ASL_RESULT = bdata::make({0x00, 0xFE, 0x9E, 0x00});
static auto ASL_SOURCE = bdata::make({0x0000, 0x1234, -1, -1});
static auto ASL_N = bdata::make({false, true, true, false});
static auto ASL_Z = bdata::make({true, false, false, true});
static auto ASL_C = bdata::make({false, true, false, true});
static auto ASL_DATA = ASL_V ^ ASL_RESULT ^ ASL_SOURCE ^ ASL_N ^ ASL_Z ^ ASL_C;
BOOST_DATA_TEST_CASE_F(Fixture, ASL_TEST, ASL_DATA, v, res, source, n, z, c)
{
    if(source != -1){
        bus->write(source, v);
        BOOST_CHECK_EQUAL(ASL(rf, bus, source, 0), true);
        BOOST_CHECK_EQUAL(bus->read(source), res);
    }else{
        rf.accumulator = v;
        BOOST_CHECK_EQUAL(ASL_ACCUM(rf, bus, 0, 0), true);
        BOOST_CHECK_EQUAL(rf.accumulator, res);
    }

    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getCarry(), c);
}

static auto LSR_V = bdata::make({0x00, 0xFF, 0x4F, 0x80});
static auto LSR_RESULT = bdata::make({0x00, 0x7F, 0x27, 0x40});
static auto LSR_SOURCE = bdata::make({0x0000, 0x1234, -1, -1});
static auto LSR_N = bdata::make({false, false, false, false});
static auto LSR_Z = bdata::make({true, false, false, false});
static auto LSR_C = bdata::make({false, true, true, false});
static auto LSR_DATA = LSR_V ^ LSR_RESULT ^ LSR_SOURCE ^ LSR_N ^ LSR_Z ^ LSR_C;
BOOST_DATA_TEST_CASE_F(Fixture, LSR_TEST, LSR_DATA, v, res, source, n, z, c)
{
    if(source != -1){
        bus->write(source, v);
        BOOST_CHECK_EQUAL(LSR(rf, bus, source, 0), true);
        BOOST_CHECK_EQUAL(bus->read(source), res);
    }else{
        rf.accumulator = v;
        BOOST_CHECK_EQUAL(LSR_ACCUM(rf, bus, 0, 0), true);
        BOOST_CHECK_EQUAL(rf.accumulator, res);
    }

    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getCarry(), c);
}

static auto ROL_V = bdata::make({0x00, 0x7F, 0x4F, 0x80});
static auto ROL_OLD_C = bdata::make({false, true, true, false});
static auto ROL_RESULT = bdata::make({0x00, 0xFF, 0x9F, 0x00});
static auto ROL_SOURCE = bdata::make({0x0000, 0x1234, -1, -1});
static auto ROL_N = bdata::make({false, true, true, false});
static auto ROL_Z = bdata::make({true, false, false, true});
static auto ROL_C = bdata::make({false, false, false, true});
static auto ROL_DATA = ROL_V ^ ROL_OLD_C ^ ROL_RESULT ^ ROL_SOURCE ^ ROL_N ^ ROL_Z ^ ROL_C;
BOOST_DATA_TEST_CASE_F(Fixture, ROL_TEST, ROL_DATA, v, old_c, res, source, n, z, c)
{
    rf.setCarry(old_c);
    if(source != -1){
        bus->write(source, v);
        BOOST_CHECK_EQUAL(ROL(rf, bus, source, 0), true);
        BOOST_CHECK_EQUAL(bus->read(source), res);
    }else{
        rf.accumulator = v;
        BOOST_CHECK_EQUAL(ROL_ACCUM(rf, bus, 0, 0), true);
        BOOST_CHECK_EQUAL(rf.accumulator, res);
    }

    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getCarry(), c);
}

static auto ROR_V = bdata::make({0x00, 0x7F, 0x4F, 0x80});
static auto ROR_OLD_C = bdata::make({false, true, true, false});
static auto ROR_RESULT = bdata::make({0x00, 0xBF, 0xA7, 0x40});
static auto ROR_SOURCE = bdata::make({0x0000, 0x1234, -1, -1});
static auto ROR_N = bdata::make({false, true, true, false});
static auto ROR_Z = bdata::make({true, false, false, false});
static auto ROR_C = bdata::make({false, true, true, false});
static auto ROR_DATA = ROR_V ^ ROR_OLD_C ^ ROR_RESULT ^ ROR_SOURCE ^ ROR_N ^ ROR_Z ^ ROR_C;
BOOST_DATA_TEST_CASE_F(Fixture, ROR_TEST, ROR_DATA, v, old_c, res, source, n, z, c)
{
    rf.setCarry(old_c);
    if(source != -1){
        bus->write(source, v);
        BOOST_CHECK_EQUAL(ROR(rf, bus, source, 0), true);
        BOOST_CHECK_EQUAL(bus->read(source), res);
    }else{
        rf.accumulator = v;
        BOOST_CHECK_EQUAL(ROR_ACCUM(rf, bus, 0, 0), true);
        BOOST_CHECK_EQUAL(rf.accumulator, res);
    }

    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getCarry(), c);
}

BOOST_AUTO_TEST_SUITE_END()