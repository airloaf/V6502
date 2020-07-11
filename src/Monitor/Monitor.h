#pragma once

#include <V6502/CPU.h>

#include "MemoryBus.h"

#include "Windows/MemoryViewerRenderer.h"
#include "Windows/CPUStatus.h"
#include "Windows/Footer.h"

#include <ncurses.h>

class Monitor{

    public:
        Monitor();
        ~Monitor();

        void init();

        void run();

    private:

        void updateWindows();

        void initializeCPU();

        void initializeNcurses();
        void deinitializeNcurses();

        void createWindows();
        void initializeWindows();
        void freeWindows();

        V6502::CPU mCPU;
        MemoryBus mBus;

        WINDOW *mStdscr;

        MemoryViewerRenderer *mProgramViewer, *mStackViewer, *mZeroPageViewer;
        CPUStatus *mCPUStatus;
        Footer *mFooter;

        uint16_t mZeroPageOffset;

};