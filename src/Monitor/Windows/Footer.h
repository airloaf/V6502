#pragma once

#include "Window.h"

class Footer: public Window {
    public:
        Footer(WINDOW *stdscr, int startX, int startY, int width, int height);
        ~Footer();

        void update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);

};