#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>

BOOST_AUTO_TEST_CASE(passing_test){
    V6502::CPU cpu;
    BOOST_CHECK(cpu.getIRQ() == false);
}