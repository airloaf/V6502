#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>

#include "MemoryBus.h"

BOOST_AUTO_TEST_SUITE(MEMORY_BUS_TESTS)

/**
 * @brief Test that the memory bus data structure actually works
 * 
 */
BOOST_AUTO_TEST_CASE(MemoryBusTest){
    MemoryBus bus;
    bus.write(0x00, 0x43);
    bus.write(0x70, 0xFF);
    bus.write(0xFF, 0x00);
    bus.write(0x02, 0x78);

    BOOST_CHECK_EQUAL(bus.read(0x00), 0x43);
    BOOST_CHECK_EQUAL(bus.read(0x70), 0xFF);
    BOOST_CHECK_EQUAL(bus.read(0xFF), 0x00);
    BOOST_CHECK_EQUAL(bus.read(0x02), 0x78);
}


BOOST_AUTO_TEST_SUITE_END()