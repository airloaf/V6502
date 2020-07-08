#include "MemoryViewerRenderer.h"

#include "../Utils/StringFormatting.h"

MemoryViewerRenderer::MemoryViewerRenderer(WINDOW *stdscr, int startX, int startY, int width, int height)
: Window(stdscr, startX, startY, width, height){
}

MemoryViewerRenderer::~MemoryViewerRenderer(){
}

void MemoryViewerRenderer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    Window::update(cpu, memoryBus);
}

void MemoryViewerRenderer::writeMemory(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    // Render title
    wmove(mWindow, 1, calculateCenterXCoordinate(mTitle, mWidth));
    wprintw(mWindow, "%s", mTitle.c_str());

    // The number of addresses to render
    int addresses = mHeight-4;
    for(int addressOffset = 0; addressOffset < addresses; addressOffset++){
        uint16_t address = mCenterAddress + addressOffset - (addresses/2);
        uint8_t value = memoryBus->read(address);

        if(mDescending){
            wmove(mWindow, mHeight - (addressOffset) - 2, 1);
        }else{
            wmove(mWindow, 3 + addressOffset, 1);
        }
        char prefix = (addressOffset == (int) (addresses/2))? '>':' ';
        wprintw(mWindow, "%c%04x: %02x", prefix, (int) address, (int) value);
    }
}