#include "CPUStatus.h"
#include "../Utils/StringFormatting.h"

#include <cstdio>
#include <bitset>

CPUStatus::CPUStatus(WINDOW *stdscr, std::size_t startX, std::size_t startY,
                     std::size_t width, std::size_t height)
: Window(stdscr, startX, startY, width, height){
}

void CPUStatus::update(V6502::CPU *cpu,
                       V6502::MemoryBus *memoryBus){

    renderBorder();

    std::string windowTitle = "CPU Status";
    renderTextCenter(windowTitle, 1);

    V6502::RegisterFile rf = cpu->getRegisterFile();
    wmove(mWindow, 3, 3);
    wprintw(mWindow, "%2s: $ %04x", "PC", (int) rf.programCounter);
    wmove(mWindow, 4, 3);
    wprintw(mWindow, "%2s: $ %04x", "SP", (int) rf.stackPointer);
    wmove(mWindow, 5, 3);
    wprintw(mWindow, "%2s: $ %4x", "A", (int) rf.accumulator);
    wmove(mWindow, 6, 3);
    wprintw(mWindow, "%2s: $ %4x", "X", (int) rf.indexX);
    wmove(mWindow, 7, 3);
    wprintw(mWindow, "%2s: $ %4x", "Y", (int) rf.indexY);
    wmove(mWindow, 8, 3);
    wprintw(mWindow, "%2s: $ %4x", "P", (int) rf.status);

    // Render the individual bits of the status register
    std::bitset<8> statusBits(rf.status);
    std::string statusBitString = statusBits.to_string();
    wmove(mWindow, 9, calculateCenterXCoordinate("Status Bits", mWidth));
    wprintw(mWindow, "%s","Status Bits"); 
    wmove(mWindow, 10, calculateCenterXCoordinate(statusBitString, mWidth));
    wprintw(mWindow, "%s", statusBitString.c_str());
    wmove(mWindow, 11, calculateCenterXCoordinate(statusBitString, mWidth));
    wprintw(mWindow, "%s", "NV-BDIZC");

}