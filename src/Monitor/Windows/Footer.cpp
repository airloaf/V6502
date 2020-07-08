#include "Footer.h"

Footer::Footer(WINDOW *stdscr, int startX, int startY, int width, int height)
: Window(stdscr, startX, startY, width, height){
}

Footer::~Footer(){

}

void Footer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    Window::update(cpu, memoryBus);
    wprintw(mWindow, "Footer");
}