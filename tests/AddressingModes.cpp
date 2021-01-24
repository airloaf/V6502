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
    BOOST_CHECK_EQUAL(decoded, pc);
    BOOST_CHECK_EQUAL(rf.programCounter, pc+1);
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
    BOOST_CHECK_EQUAL(rf.programCounter, pc+2);

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
    BOOST_CHECK_EQUAL(rf.programCounter, pc+1);

}

static auto ZP_X_PC = bdata::make({0xF000, 0x1234, 0xDEAD, 0xBEEF});
static auto ZP_X_INDEX = bdata::make({0x00, 0xFF, 0x4D, 0xD6});
static auto ZP_X_VALUE = bdata::make({0xFF, 0x00, 0x1, 0x2});
static auto ZP_X_EXPECTED = bdata::make({0x00FF, 0x00FF, 0x004E, 0x00D8});
static auto ZP_X_DATA = ZP_X_PC ^ ZP_X_INDEX ^ ZP_X_VALUE ^ ZP_X_EXPECTED;
BOOST_DATA_TEST_CASE_F(Fixture, ZERO_PAGE_X_TEST, ZP_X_DATA, pc, index, x, expected)
{
    rf.programCounter = pc;
    rf.indexX = x;
    bus->write(rf.programCounter, index);
    uint16_t decoded;

    BOOST_CHECK_EQUAL(absolute(rf, bus, decoded, 0), false);
    BOOST_CHECK_EQUAL(absolute(rf, bus, decoded, 1), true);
    BOOST_CHECK_EQUAL(decoded, expected);
    BOOST_CHECK_EQUAL(rf.programCounter, pc+1);

}

static auto ZP_Y_PC = bdata::make({0xF000, 0x1234, 0xDEAD, 0xBEEF});
static auto ZP_Y_INDEY = bdata::make({0x00, 0xFF, 0x4D, 0xD6});
static auto ZP_Y_VALUE = bdata::make({0xFF, 0x00, 0x1, 0x2});
static auto ZP_Y_EYPECTED = bdata::make({0x00FF, 0x00FF, 0x004E, 0x00D8});
static auto ZP_Y_DATA = ZP_Y_PC ^ ZP_Y_INDEY ^ ZP_Y_VALUE ^ ZP_Y_EYPECTED;
BOOST_DATA_TEST_CASE_F(Fixture, ZERO_PAGE_Y_TEST, ZP_Y_DATA, pc, index, y, expected)
{
    rf.programCounter = pc;
    rf.indexY = y;
    bus->write(rf.programCounter, index);
    uint16_t decoded;

    BOOST_CHECK_EQUAL(absolute(rf, bus, decoded, 0), false);
    BOOST_CHECK_EQUAL(absolute(rf, bus, decoded, 1), true);
    BOOST_CHECK_EQUAL(decoded, expected);
    BOOST_CHECK_EQUAL(rf.programCounter, pc+1);

}

static auto IDX_ABS_X_PC = bdata::make({0xF000, 0x1234, 0xDEAD, 0xBEEF});
static auto IDX_ABS_X_LOW = bdata::make({0x34, 0xFF, 0x01, 0x12});
static auto IDX_ABS_X_HIGH = bdata::make({0x12, 0xFF, 0x00, 0x12});
static auto IDX_ABS_X_INDEX = bdata::make({0xCB, 0x00, 0xFE, 0x30});
static auto IDX_ABS_X_EXPECTED = bdata::make({0x12FF, 0xFFFF, 0x00FF, 0x1242});
static auto IDX_ABS_X_DATA = IDX_ABS_X_PC ^ IDX_ABS_X_LOW ^ IDX_ABS_X_HIGH ^ IDX_ABS_X_INDEX ^ IDX_ABS_X_EXPECTED;
BOOST_DATA_TEST_CASE_F(Fixture, INDEXED_ABSOLUTE_X_NO_BOUNDARY, IDX_ABS_X_DATA, pc, low, high, index, expected)
{
    rf.programCounter = pc;
    rf.indexX = index;
    bus->write(rf.programCounter, low);
    bus->write(rf.programCounter+1, high);
    uint16_t decoded;
    
    BOOST_CHECK_EQUAL(indexedAbsoluteX(rf, bus, decoded, 0), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteX(rf, bus, decoded, 1), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteX(rf, bus, decoded, 2), true);

    BOOST_CHECK_EQUAL(decoded, expected);
}

// static auto IDX_ABS_X_PC = bdata::make({0xF000, 0x1234, 0xDEAD, 0xBEEF});
// static auto IDX_ABS_X_LOW = bdata::make({0x34, 0xFF, 0x01, 0x12});
// static auto IDX_ABS_X_HIGH = bdata::make({0x12, 0xFF, 0x00, 0x12});
static auto IDX_ABS_X_INDEX_BOUNDARY = bdata::make({0xCC, 0xFF, 0xFF, 0xF0});
static auto IDX_ABS_X_EXPECTED_BOUNDARY = bdata::make({0x1300, 0x0100, 0x00FF, 0x1302});
static auto IDX_ABS_X_DATA_BOUNDARY = IDX_ABS_X_PC ^ IDX_ABS_X_LOW ^ IDX_ABS_X_HIGH ^ IDX_ABS_X_INDEX_BOUNDARY ^ IDX_ABS_X_EXPECTED_BOUNDARY;
BOOST_DATA_TEST_CASE_F(Fixture, INDEXED_ABSOLUTE_X_BOUNDARY, IDX_ABS_X_DATA_BOUNDARY, pc, low, high, index, expected)
{
    rf.programCounter = pc;
    rf.indexX = index;
    bus->write(rf.programCounter, low);
    bus->write(rf.programCounter+1, high);
    uint16_t decoded;
    
    BOOST_CHECK_EQUAL(indexedAbsoluteX(rf, bus, decoded, 0), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteX(rf, bus, decoded, 1), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteX(rf, bus, decoded, 2), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteX(rf, bus, decoded, 3), true);

    BOOST_CHECK_EQUAL(decoded, expected);
}

static auto IDY_ABS_Y_PC = bdata::make({0xF000, 0x1234, 0xDEAD, 0xBEEF});
static auto IDY_ABS_Y_LOW = bdata::make({0x34, 0xFF, 0x00, 0x12});
static auto IDY_ABS_Y_HIGH = bdata::make({0x12, 0xFF, 0x00, 0x12});
static auto IDY_ABS_Y_INDEX = bdata::make({0xCB, 0x00, 0xFF, 0x30});
static auto IDY_ABS_Y_EXPECTED = bdata::make({0x12FF, 0xFFFF, 0x00FF, 0x1242});
static auto IDY_ABS_Y_DATA = IDY_ABS_Y_PC ^ IDY_ABS_Y_LOW ^ IDY_ABS_Y_HIGH ^ IDY_ABS_Y_INDEX ^ IDY_ABS_Y_EXPECTED;
BOOST_DATA_TEST_CASE_F(Fixture, INDEXED_ABSOLUTE_Y_NO_BOUNDARY, IDY_ABS_Y_DATA, pc, low, high, index, expected)
{
    rf.programCounter = pc;
    rf.indexY = index;
    bus->write(rf.programCounter, low);
    bus->write(rf.programCounter+1, high);
    uint16_t decoded;
    
    BOOST_CHECK_EQUAL(indexedAbsoluteY(rf, bus, decoded, 0), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteY(rf, bus, decoded, 1), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteY(rf, bus, decoded, 2), true);

    BOOST_CHECK_EQUAL(decoded, expected);
}

static auto IDY_ABS_Y_INDEX_BOUNDARY = bdata::make({0xCC, 0xFF, 0xFF, 0xF0});
static auto IDY_ABS_Y_EXPECTED_BOUNDARY = bdata::make({0x1300, 0x0100, 0x00FF, 0x1302});
static auto IDY_ABS_Y_DATA_BOUNDARY = IDY_ABS_Y_PC ^ IDY_ABS_Y_LOW ^ IDY_ABS_Y_HIGH ^ IDY_ABS_Y_INDEX_BOUNDARY ^ IDY_ABS_Y_EXPECTED_BOUNDARY;
BOOST_DATA_TEST_CASE_F(Fixture, INDEXED_ABSOLUTE_Y_BOUNDARY, IDY_ABS_Y_DATA_BOUNDARY, pc, low, high, index, expected)
{
    rf.programCounter = pc;
    rf.indexY = index;
    bus->write(rf.programCounter, low);
    bus->write(rf.programCounter+1, high);
    uint16_t decoded;
    
    BOOST_CHECK_EQUAL(indexedAbsoluteY(rf, bus, decoded, 0), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteY(rf, bus, decoded, 1), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteY(rf, bus, decoded, 2), false);
    BOOST_CHECK_EQUAL(indexedAbsoluteY(rf, bus, decoded, 3), true);

    BOOST_CHECK_EQUAL(decoded, expected);
}

static auto REL_PC = bdata::make({0x0000, 0x1234, 0xDEAD, 0xBEEF});
BOOST_DATA_TEST_CASE_F(Fixture, RELATIVE_TEST, REL_PC, pc)
{
    rf.programCounter = pc;
    uint16_t decoded;

    BOOST_CHECK_EQUAL(relative(rf, bus, decoded, 0), true);
    BOOST_CHECK_EQUAL(decoded, pc);
    BOOST_CHECK_EQUAL(rf.programCounter, pc+1);
}

BOOST_AUTO_TEST_SUITE_END()