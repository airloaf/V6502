#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>

BOOST_AUTO_TEST_SUITE(cpu_instruction_tests)

using namespace V6502;

struct CPUFixture {
    CPUFixture(){}
    ~CPUFixture(){}

    V6502::CPU cpu;
};

BOOST_AUTO_TEST_SUITE_END()