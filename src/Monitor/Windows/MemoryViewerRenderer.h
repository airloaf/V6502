#pragma once

#include "Window.h"

#include <vector>
#include <string>

class MemoryViewerRenderer: public Window {
    public:
        MemoryViewerRenderer(WINDOW *stdscr, std::size_t startX, std::size_t
                             startY, std::size_t width, std::size_t height);

        void update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);

        void setTitle(std::string title);

        void setRenderDescending(bool descending);

        void centerOnAddress(uint16_t address);

    private:
        
        void renderMemory(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);

        std::string mTitle;
        
        bool mRenderDescending;
        
        uint16_t mCenterAddress;

};