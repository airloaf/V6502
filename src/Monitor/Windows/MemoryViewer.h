#include "Window.h"

class MemoryViewer: public Window {
    public:
        MemoryViewer(WINDOW *stdscr, int startX, int startY, int width, int height);
        ~MemoryViewer();

        void update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);

};