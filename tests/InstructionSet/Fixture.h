#pragma once

#include <boost/test/unit_test.hpp>
#include <V6502/CPU.h>
#include <V6502/RegisterFile.h>

#include "../MemoryBus.h"

struct Fixture {
    MemoryBus *bus;
    V6502::RegisterFile rf;

    Fixture(){
        bus = new MemoryBus();
    }
    ~Fixture(){
        delete bus;
    }
};