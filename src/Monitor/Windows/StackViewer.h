#pragma once

#include "MemoryViewerRenderer.h"

class StackViewer: public MemoryViewerRenderer{
    public:
        StackViewer(WINDOW *stdscr, int startX, int startY, int width, int height);
        ~StackViewer();

        void update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);
};