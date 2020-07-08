#include "ProgramViewer.h"

#include "../Utils/StringFormatting.h"

ProgramViewer::ProgramViewer(WINDOW *stdscr, int startX, int startY, int width, int height)
: MemoryViewerRenderer(stdscr, startX, startY, width, height){

    // Ascend as we go downwards
    mDescending = false;

    // Set title
    mTitle = "Program Viewer";
}

ProgramViewer::~ProgramViewer(){
}

void ProgramViewer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    Window::update(cpu, memoryBus);

    // Center on the current value of the CPU program counter
    mCenterAddress = cpu->getRegisterFile().programCounter;

    MemoryViewerRenderer::writeMemory(cpu, memoryBus);
}