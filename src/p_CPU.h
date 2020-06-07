#pragma once

#include <V6502/CPU.h>

using namespace V6502;

class CPU::pimpl {

    public:
        pimpl();
        ~pimpl();

        void tick();
        void reset();

        void setAddressBus(AddressBus *addressBus);
        
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

        // Address bus to read/write from/to
        V6502::AddressBus *mAddressBus;

        // Reset boolean. Resetting the 6502 takes 6 cycles, so a boolean is used to track that we are resetting
        bool mReset;
        // The current reset cycle. Resetting the 6502 takes 6 cycles, so this is used to keep track of which cycle we are on
        int mCurrentResetCycle;
};