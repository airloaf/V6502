#include "StackViewer.h"

#include "../Utils/StringFormatting.h"

StackViewer::StackViewer(WINDOW *stdscr, int startX, int startY, int width, int height)
: MemoryViewerRenderer(stdscr, startX, startY, width, height){
    // Descend in memory
    mDescending = true;

    // Set title
    mTitle = "Stack Viewer";
}

StackViewer::~StackViewer(){
}

void StackViewer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    Window::update(cpu, memoryBus);

    // Center on the current value of the CPU Stack Pointer
    mCenterAddress = cpu->getRegisterFile().stackPointer;

    MemoryViewerRenderer::writeMemory(cpu, memoryBus);
}