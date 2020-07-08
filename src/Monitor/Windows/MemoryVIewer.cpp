#include "MemoryViewer.h"

MemoryViewer::MemoryViewer(WINDOW *stdscr, int startX, int startY, int width, int height)
: Window(stdscr, startX, startY, width, height){
}

MemoryViewer::~MemoryViewer(){

}

void MemoryViewer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    Window::update(cpu, memoryBus);
    wprintw(mWindow, "Memory Viewer");
}