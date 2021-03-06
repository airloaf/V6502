#pragma once

#include <V6502/CPU.h>

#include "Instructions/Instruction.h"
#include "Instructions/InstructionFactory.h"

using namespace V6502;

class CPU::pimpl {

    public:
        pimpl();
        ~pimpl();

        void tick();
        void reset();

        void setMemoryBus(MemoryBus *memoryBus);
        
        bool getNMI();
        void setNMI(bool set);

        bool getIRQ();
        void setIRQ(bool set);

        RegisterFile getRegisterFile();
        void setRegisterFile(RegisterFile rf);

    private:
        V6502::RegisterFile mRegisterFile; // Register file for the CPU

        // The 6502 has two signal, NMI and IRQ, which can signal interrupts
        // As the name suggests, the NMI cannot be masked out, while the IRQ can
        bool mNMI, mIRQ;

        // Whether or not an interrupt is occuring
        bool mInInterruptHandler;
        // Whether or not the interrupt is an NMI interrupt
        // This is for the case where we are in the IRQ interrupt sequence,
        // but if an NMI interrupt is triggered while we are fetching the next
        // program counter, we need to choose the correct address
        bool mIsNMIInterrupt;

        // The current cycle of the interrupt sequence. Takes 7 cycles, similar to BRK
        int mInterruptSequenceCycle;

        // Address bus to read/write from/to
        V6502::MemoryBus *mMemoryBus;

        // Reset boolean. Resetting the 6502 takes 6 cycles, so a boolean is used to track that we are resetting
        bool mReset;
        // The current reset cycle. Resetting the 6502 takes 6 cycles, so this is used to keep track of which cycle we are on
        int mCurrentResetCycle;

        // The current instruction
        Instruction mInstruction;
};