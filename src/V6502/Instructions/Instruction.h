#pragma once

#include "InstructionFactory.h"
#include <V6502/RegisterFile.h>
#include <V6502/MemoryBus.h>

using namespace V6502;

class Instruction{
    public:
        Instruction();
        ~Instruction();

        void init(InstructionMetaInfo instructionInfo);

        /**
         * @brief Executes a single cycle of the instruction
         */
        void tick(MemoryBus *memoryBus, RegisterFile &rf);

        /**
         * @brief Determines if the instruction has completed.
         * 
         * @return true 
         * @return false 
         */
        bool isFinished();

        /**
         * @brief Get the Instruction Type
         * 
         * @return InstructionType 
         */
        InstructionType getType();

    private:
        InstructionMetaInfo mInfo;

        int mInstructionCycle; // current instruction operation cycle
        int mAddressingCycle; // current addressing mode cycle

        bool mAddressingFinished;
        bool mInstructionFinished;
        bool mFinished;

        uint16_t mDecodedAddress;
};