#include "Footer.h"

#include "../Utils/StringFormatting.h"

Footer::Footer(WINDOW *stdscr, int startX, int startY, int width, int height)
: Window(stdscr, startX, startY, width, height){
}

Footer::~Footer(){

}

void Footer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){

    renderBorder();

    std::string title = "Instructions";
    renderTextCenter(title, 1);

    wmove(mWindow, 2, 1);
    wprintw(mWindow, "- s: Step");
    wmove(mWindow, 3, 1);
    wprintw(mWindow, "- c: Toggle Continuous Execution");
    wmove(mWindow, 4, 1);
    wprintw(mWindow, "- q: Quit");

}