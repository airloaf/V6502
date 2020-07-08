#pragma once

#include "Window.h"
#include "ProgramViewer.h"
#include "StackViewer.h"

class MemoryViewer: public Window {
    public:
        MemoryViewer(WINDOW *stdscr, int startX, int startY, int width, int height);
        ~MemoryViewer();

        void update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);

    private:
        ProgramViewer mProgramViewer;
        StackViewer mStackViewer;

};