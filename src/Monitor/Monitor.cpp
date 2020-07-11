#include "Monitor.h"

#include <thread>
#include <chrono>
#include <iostream>

#include "Utils/FileLoaders.h"

Monitor::Monitor():
    mStdscr(nullptr),
    mProgramViewer(nullptr),
    mStackViewer(nullptr),
    mZeroPageViewer(nullptr),
    mCPUStatus(nullptr),
    mFooter(nullptr)
{}

Monitor::~Monitor(){
    freeWindows();
    deinitializeNcurses();
}

void Monitor::init(){
    initializeNcurses();
    createWindows();
    initializeWindows();
    initializeCPU();
}
void Monitor::run(){
    bool quit = false;
    char key;

    while(!quit){
        updateWindows();

        // Get the next key press
        key = getch();
        switch(key){
            case 'q':
                quit = true;
            break;
            case 'c':
                // stop blocking the getch call
                timeout(0);
                key = getch();
                while(key != 'c'){
                    std::this_thread::sleep_for(std::chrono::microseconds(100));
                    mCPU.tick();
                    updateWindows();
                    key = getch();
                }
                timeout(-1);
                break;
            case 's':
                mCPU.tick();
            break;
        }
    }
}

void Monitor::updateWindows(){
    // Recenter Windows
    V6502::RegisterFile rf = mCPU.getRegisterFile();
    mProgramViewer->centerOnAddress(rf.programCounter);
    mStackViewer->centerOnAddress(0x100 + rf.stackPointer);
    mZeroPageViewer->centerOnAddress(0x0000);

    // Update Windows
    mProgramViewer->update(&mCPU, &mBus);
    mStackViewer->update(&mCPU, &mBus);
    mZeroPageViewer->update(&mCPU, &mBus);
    mCPUStatus->update(&mCPU, &mBus);
    mFooter->update(&mCPU, &mBus);

    // Update standard screen
    touchwin(mStdscr);
    wrefresh(mStdscr);
}

void Monitor::createWindows(){
    int numRenderers = 4;
    mProgramViewer = new MemoryViewerRenderer(mStdscr,
        (float) COLS*((float) 0/numRenderers),
        0, COLS / numRenderers, LINES * 0.75);
    mStackViewer = new MemoryViewerRenderer(mStdscr,
        (float) COLS*((float) 1/numRenderers),
        0, COLS / numRenderers, LINES * 0.75);
    mZeroPageViewer = new MemoryViewerRenderer(mStdscr,
        (float) COLS*((float) 2/numRenderers),
        0, COLS / numRenderers, LINES * 0.75);

    mCPUStatus = new CPUStatus(mStdscr,
        (float) COLS*((float) (numRenderers-1)/numRenderers), 0,
        COLS / numRenderers, LINES * 0.75);

    mFooter = new Footer(mStdscr, 0, LINES * 0.75, COLS, LINES * 0.25);
}

void Monitor::initializeCPU(){
    mCPU.setMemoryBus(&mBus);
    
    // Read binary file into memory
    if(!loadBinaryFile("programs/TTL6502.bin", &mBus, 0xE000, 0x2000)){
        endwin();
        std::cout << "Could not load file" << std::endl;
    }

    // Skip the power up sequence
    for(int i = 0; i < 6; i++){
        mCPU.tick();
    }

    V6502::RegisterFile rf = mCPU.getRegisterFile();
    rf.programCounter = 0xE000;
    mCPU.setRegisterFile(rf);
}

void Monitor::initializeWindows(){
    mProgramViewer->setTitle("Program");
    mProgramViewer->setRenderDescending(false);

    mStackViewer->setTitle("Stack");
    mStackViewer->setRenderDescending(true);
    
    mZeroPageViewer->setTitle("Zero Page");
    mZeroPageViewer->setRenderDescending(false);
}

void Monitor::initializeNcurses(){
    mStdscr = initscr();
    curs_set(0);
    noecho();
}

void Monitor::freeWindows(){
    delete mProgramViewer;
    delete mStackViewer;
    delete mZeroPageViewer;
}

void Monitor::deinitializeNcurses(){
    endwin();
}