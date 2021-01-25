#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/InstructionSet/InstructionSet.h"

#include "Fixture.h"

namespace bdata = boost::unit_test::data;

using namespace V6502::InstructionSet;

BOOST_AUTO_TEST_SUITE(ARITHMETIC_INSTRUCTIONS)

static auto AND_V = bdata::make({0x00, 0xFF, 0x43});
static auto AND_ACCUM = bdata::make({0xFF, 0x00, 0xDB});
static auto AND_RESULT = bdata::make({0x00, 0x00, 0x43});
static auto AND_DATA = AND_V ^ AND_ACCUM ^ AND_RESULT;
BOOST_DATA_TEST_CASE_F(Fixture, AND_TEST, AND_DATA, v, accum, result)
{
    rf.accumulator = accum;
    bus->write(0x0000, v);

    BOOST_CHECK_EQUAL(AND(rf, bus, 0x0000, 0), true);
    BOOST_CHECK_EQUAL(rf.accumulator, result);
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
    }else{
        rf.accumulator = v;
        BOOST_CHECK_EQUAL(ASL_ACCUM(rf, bus, 0, 0), true);
    }

    BOOST_CHECK_EQUAL(rf.accumulator, res);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
    BOOST_CHECK_EQUAL(rf.getCarry(), c);
}

BOOST_AUTO_TEST_SUITE_END()