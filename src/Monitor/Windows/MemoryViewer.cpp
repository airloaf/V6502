#include "MemoryViewer.h"

MemoryViewer::MemoryViewer(WINDOW *stdscr, int startX, int startY, int width, int height)
: Window(stdscr, startX, startY, width, height),
mProgramViewer(mWindow, startX, startY, width/2, height),
mStackViewer(mWindow, startX + width/2, startY, width/2, height){
}

MemoryViewer::~MemoryViewer(){
}

void MemoryViewer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    Window::update(cpu, memoryBus);
    mProgramViewer.update(cpu, memoryBus);
    mStackViewer.update(cpu, memoryBus);
}