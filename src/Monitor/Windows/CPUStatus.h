#include "Window.h"

class CPUStatus: public Window {
    public:
        CPUStatus(WINDOW *stdscr, int startX, int startY, int width, int height);
        ~CPUStatus();

        void update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);

};