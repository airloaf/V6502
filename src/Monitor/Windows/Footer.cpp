#include "Footer.h"

#include "../Utils/StringFormatting.h"

Footer::Footer(WINDOW *stdscr, int startX, int startY, int width, int height)
: Window(stdscr, startX, startY, width, height){
}

Footer::~Footer(){

}

void Footer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    Window::update(cpu, memoryBus);

    std::string title = "Instructions";
    wmove(mWindow, 1, calculateCenterXCoordinate(title, mWidth));
    wprintw(mWindow, title.c_str());

    wmove(mWindow, 2, 1);
    wprintw(mWindow, "- s: Step");
    wmove(mWindow, 3, 1);
    wprintw(mWindow, "- c: Toggle Continuous Execution");
    wmove(mWindow, 4, 1);
    wprintw(mWindow, "- q: Quit");

}