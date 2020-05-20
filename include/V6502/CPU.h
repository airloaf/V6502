#pragma once

#include "AddressBus.h"
#include "RegisterFile.h"

namespace V6502 {
    /**
     * @brief 6502 processor
     */
    class CPU{
        public:
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
             * @brief Sets the Address Bus
             * 
             * @param addressBus - The address bus to use
             */
            void setAddressBus(AddressBus *addressBus);

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
            V6502::RegisterFile mRegisterFile; // Register file for the CPU

            // The 6502 has two signal, NMI and IRQ, which can signal interrupts
            // As the name suggests, the NMI cannot be masked out, while the IRQ can
            bool mNMI, mIRQ;

            // Address bus to read/write from/to
            V6502::AddressBus *mAddressBus;
    };
}