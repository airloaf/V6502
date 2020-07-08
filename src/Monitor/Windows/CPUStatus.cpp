#include "CPUStatus.h"
#include "../Utils/StringFormatting.h"

#include <bitset>

CPUStatus::CPUStatus(WINDOW *stdscr, int startX, int startY, int width, int height)
: Window(stdscr, startX, startY, width, height){
}

CPUStatus::~CPUStatus(){

}

void CPUStatus::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    Window::update(cpu, memoryBus);

    // Render title
    std::string title = "CPU Status";
    wmove(mWindow, 1, calculateCenterXCoordinate(title, mWidth));
    wprintw(mWindow, "CPU Status");

    // Render the registers
    V6502::RegisterFile rf = cpu->getRegisterFile();
    wmove(mWindow, 3, 3);
    wprintw(mWindow, "%2s: $ %04x", "PC", (int) rf.programCounter);
    wmove(mWindow, 4, 3);
    wprintw(mWindow, "%2s: $ %04x", "SP", (int) rf.stackPointer);
    wmove(mWindow, 5, 3);
    wprintw(mWindow, "%2s: $ %4x", "P", (int) rf.status);
    wmove(mWindow, 6, 3);
    wprintw(mWindow, "%2s: $ %4x", "X", (int) rf.indexX);
    wmove(mWindow, 7, 3);
    wprintw(mWindow, "%2s: $ %4x", "Y", (int) rf.indexY);

    // Render the individual bits of the status register
    std::bitset<8> statusBits(rf.status);
    std::string statusBitString = statusBits.to_string();
    wmove(mWindow, 8, calculateCenterXCoordinate("Status Bits", mWidth));
    wprintw(mWindow, "%s","Status Bits"); 
    wmove(mWindow, 9, calculateCenterXCoordinate(statusBitString, mWidth));
    wprintw(mWindow, "%s", statusBitString.c_str());
    wmove(mWindow, 10, calculateCenterXCoordinate(statusBitString, mWidth));
    wprintw(mWindow, "%s", "NV-BDIZC");

}