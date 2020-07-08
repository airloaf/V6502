#pragma once

#include "MemoryViewerRenderer.h"

class ProgramViewer: public MemoryViewerRenderer{
    public:
        ProgramViewer(WINDOW *stdscr, int startX, int startY, int width, int height);
        ~ProgramViewer();

        void update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);
};