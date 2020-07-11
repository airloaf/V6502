#include "MemoryViewerRenderer.h"

#include "../Utils/StringFormatting.h"

MemoryViewerRenderer::MemoryViewerRenderer(WINDOW *stdscr, std::size_t startX,
                                           std::size_t startY, std::size_t width,
                                           std::size_t height)
: Window(stdscr, startX, startY, width, height){}

void MemoryViewerRenderer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    renderBorder();
    renderTextCenter(mTitle, 1);
    renderMemory(cpu, memoryBus);
}

void MemoryViewerRenderer::renderMemory(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){

    // The number of addresses to render
    int addresses = mHeight-4;
    for(int addressOffset = 0; addressOffset < addresses; addressOffset++){
        uint16_t address = mCenterAddress + addressOffset - (addresses/2);
        uint8_t value = memoryBus->read(address);

        if(mRenderDescending){
            wmove(mWindow, mHeight - (addressOffset) - 2, 1);
        }else{
            wmove(mWindow, 3 + addressOffset, 1);
        }
        attron(A_BLINK);
        char prefix = (addressOffset == (int) (addresses/2))? '>':' ';
        wprintw(mWindow, "%c%04x: %02x", prefix, (int) address, (int) value);
    }
        attroff(A_BLINK);
}

void MemoryViewerRenderer::setTitle(std::string title){
    mTitle = title;
}

void MemoryViewerRenderer::setRenderDescending(bool descending){
    mRenderDescending = descending;
}

void MemoryViewerRenderer::centerOnAddress(uint16_t address){
    mCenterAddress = address;
}