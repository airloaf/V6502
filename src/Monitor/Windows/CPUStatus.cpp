#include "CPUStatus.h"

CPUStatus::CPUStatus(WINDOW *stdscr, int startX, int startY, int width, int height)
: Window(stdscr, startX, startY, width, height){
}

CPUStatus::~CPUStatus(){

}

void CPUStatus::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    Window::update(cpu, memoryBus);
    wprintw(mWindow, "CPU Status");
}