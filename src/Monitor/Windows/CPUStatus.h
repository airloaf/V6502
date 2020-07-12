#pragma once

#include "Window.h"

class CPUStatus: public Window {
    public:
        CPUStatus(WINDOW *stdscr,
                  std::size_t startX,
                  std::size_t startY,
                  std::size_t width,
                  std::size_t height);

        void update(V6502::CPU *cpu,
                    V6502::MemoryBus *memoryBus);

};