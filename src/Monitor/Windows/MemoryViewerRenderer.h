#pragma once

#include "Window.h"

#include <vector>
#include <string>

class MemoryViewerRenderer: public Window {
    public:
        MemoryViewerRenderer(WINDOW *stdscr, int startX, int startY, int width, int height);
        ~MemoryViewerRenderer();

        void update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);

    protected:
        // Title of the window
        std::string mTitle;

        // Should the memory be printed in descending order
        bool mDescending;

        // The address to center on
        uint16_t mCenterAddress;

        /**
         * @brief Writes the memory values into the window
         * 
         * @param cpu - cpu reference
         * @param memoryBus - memorybus reference
         */
        void writeMemory(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);
};