#pragma once

#include "MemoryBus.h"
#include "RegisterFile.h"

namespace V6502 {
    /**
     * @brief 6502 processor
     */
    class CPU{
        public:

            CPU();
            ~CPU();

            /**
             * @brief Executes a single cycle on the processor
             * 
             */
            void tick();

            /**
             * @brief Resets the processor
             * 
             */
            void reset();

            /**
             * @brief Sets the Memory Bus
             * 
             * @param addressBus - The memory bus to use
             */
            void setMemoryBus(MemoryBus *memoryBus);

            /**
             * @brief Returns the NMI signal
             * 
             * @return the NMI signal
             */
            bool getNMI();

            /**
             * @brief Sets the NMI signal
             * 
             * @param set - The value to set the signal to
             */
            void setNMI(bool set);
            /**
             * @brief Returns the IRQ signal
             * 
             * @return the IRQ signal
             */
            bool getIRQ();

            /**
             * @brief Sets the IRQ signal
             * 
             * @param set - The value to set the signal to
             */
            void setIRQ(bool set);

            /**
             * @brief Gets the Register File
             * 
             * @return RegisterFile
             */
            RegisterFile getRegisterFile();

            /**
             * @brief Set the Register File object
             * 
             * @param rf - the new register file
             */
            void setRegisterFile(RegisterFile rf);

        private:
            class pimpl; // Pointer to implementation. Abstract implementation details away from the header.
            pimpl *implementation; // actual implementation
    };
}