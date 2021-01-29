#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "../src/V6502/Instructions/InstructionSet/InstructionSet.h"

namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(TRANSFER_INSTRUCTIONS)

static auto TAX_ACCUM = bdata::make({0x00, 0xFF, 0x12});
static auto TAX_INDEXX = bdata::make({0x00, 0x00, 0x34});
static auto TAX_N = bdata::make({false, true, false});
static auto TAX_Z = bdata::make({true, false, false});
static auto TAX_DATA = TAX_ACCUM ^ TAX_INDEXX ^ TAX_N ^ TAX_Z;

BOOST_DATA_TEST_CASE(TAX, TAX_DATA, a, x, n, z)
{
    // Arrange
    V6502::RegisterFile rf;
    rf.accumulator = a;
    rf.indexX = x;

    // Act
    V6502::InstructionSet::TAX(rf, nullptr, 0, 0);

    // Assert
    BOOST_CHECK_EQUAL(rf.indexX, rf.accumulator);
    BOOST_CHECK_EQUAL(rf.indexX, a);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
}

static auto TAY_ACCUM = bdata::make({0x00, 0xFF, 0x12});
static auto TAY_INDEXY = bdata::make({0x00, 0x00, 0x34});
static auto TAY_N = bdata::make({false, true, false});
static auto TAY_Z = bdata::make({true, false, false});
static auto TAY_DATA = TAY_ACCUM ^ TAY_INDEXY ^ TAY_N ^ TAY_Z;

BOOST_DATA_TEST_CASE(TAY, TAY_DATA, a, y, n, z)
{
    // Arrange
    V6502::RegisterFile rf;
    rf.accumulator = a;
    rf.indexY = y;

    // Act
    V6502::InstructionSet::TAY(rf, nullptr, 0, 0);

    // Assert
    BOOST_CHECK_EQUAL(rf.indexY, rf.accumulator);
    BOOST_CHECK_EQUAL(rf.indexY, a);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
}

static auto TSX_STACK = bdata::make({0x00, 0xFF, 0x12});
static auto TSX_INDEXX = bdata::make({0x00, 0x00, 0x34});
static auto TSX_N = bdata::make({false, true, false});
static auto TSX_Z = bdata::make({true, false, false});
static auto TSX_DATA = TSX_STACK ^ TSX_INDEXX ^ TSX_N ^ TSX_Z;

BOOST_DATA_TEST_CASE(TSX, TSX_DATA, s, x, n, z)
{
    // Arrange
    V6502::RegisterFile rf;
    rf.stackPointer = s;
    rf.indexX = x;

    // Act
    V6502::InstructionSet::TSX(rf, nullptr, 0, 0);

    // Assert
    BOOST_CHECK_EQUAL(rf.indexX, rf.stackPointer);
    BOOST_CHECK_EQUAL(rf.indexX, s);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
}

static auto TXA_ACCUM = bdata::make({0x00, 0x00, 0x12});
static auto TXA_INDEXX = bdata::make({0x00, 0xFF, 0x34});
static auto TXA_N = bdata::make({false, true, false});
static auto TXA_Z = bdata::make({true, false, false});
static auto TXA_DATA = TXA_ACCUM ^ TXA_INDEXX ^ TXA_N ^ TXA_Z;
BOOST_DATA_TEST_CASE(TXA, TXA_DATA, a, x, n, z)
{
    // Arrange
    V6502::RegisterFile rf;
    rf.accumulator = a;
    rf.indexX = x;

    // Act
    V6502::InstructionSet::TXA(rf, nullptr, 0, 0);

    // Assert
    BOOST_CHECK_EQUAL(rf.indexX, rf.accumulator);
    BOOST_CHECK_EQUAL(rf.indexX, x);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
}

static auto TXS_STACK = bdata::make({0x00, 0x00, 0x12});
static auto TXS_INDEXX = bdata::make({0x00, 0xFF, 0x34});
static auto TXS_DATA = TXS_STACK ^ TXS_INDEXX;

BOOST_DATA_TEST_CASE(TXS, TXS_DATA, s, x)
{
    // Arrange
    V6502::RegisterFile rf;
    rf.stackPointer = s;
    rf.indexX = x;

    // Act
    V6502::InstructionSet::TXS(rf, nullptr, 0, 0);

    // Assert
    BOOST_CHECK_EQUAL(rf.indexX, rf.stackPointer);
    BOOST_CHECK_EQUAL(rf.indexX, x);
}

static auto TYA_ACCUM = bdata::make({0x00, 0x00, 0x12});
static auto TYA_INDEXY = bdata::make({0x00, 0xFF, 0x34});
static auto TYA_N = bdata::make({false, true, false});
static auto TYA_Z = bdata::make({true, false, false});
static auto TYA_DATA = TYA_ACCUM ^ TYA_INDEXY ^ TYA_N ^ TYA_Z;

BOOST_DATA_TEST_CASE(TYA, TYA_DATA, a, y, n, z)
{
    // Arrange
    V6502::RegisterFile rf;
    rf.accumulator = a;
    rf.indexY = y;

    // Act
    V6502::InstructionSet::TYA(rf, nullptr, 0, 0);

    // Assert
    BOOST_CHECK_EQUAL(rf.indexY, rf.accumulator);
    BOOST_CHECK_EQUAL(rf.indexY, y);
    BOOST_CHECK_EQUAL(rf.getNegative(), n);
    BOOST_CHECK_EQUAL(rf.getZero(), z);
}

BOOST_AUTO_TEST_SUITE_END()