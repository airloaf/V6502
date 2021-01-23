#pragma once

#include "Arithmetic.h"
#include "Branch.h"
#include "Memory.h"
#include "Stack.h"
#include "Status.h"
#include "Transfer.h"

namespace V6502
{
    namespace InstructionSet
    {
        // MISC
        bool NOP(RegisterFile &rf, MemoryBus *bus, uint16_t decoded, int cycle);
    }; // namespace InstructionSet
} // namespace V6502