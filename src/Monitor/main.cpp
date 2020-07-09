#include <ncurses.h>

#include <V6502/CPU.h>

#include <iostream>

#include "Windows/MemoryViewer.h"
#include "Windows/CPUStatus.h"
#include "Windows/Footer.h"

#include "MemoryBus.h"

#include "Utils/FileLoaders.h"

#include <thread>
#include <chrono>

int main(int argc, char *argv[]){
    // Standard screen reference
    WINDOW *stdscr = nullptr;

    // Initialize ncurses
    stdscr = initscr();

    // Check for error
    if(stdscr == nullptr){
        endwin();
        return -1;
    }

    // Hide the cursor
    curs_set(0);

    // don't echo the pressed keys
    noecho();

    // Create CPU
    V6502::CPU cpu;
    MemoryBus bus;
    cpu.setMemoryBus(&bus);

    // Skip the powerup ticks
    for(int i = 0; i < 6; i++){
        cpu.tick();
    }

    // Read binary file into memory
    if(!loadBinaryFile("programs/6502_functional_test.bin", &bus)){
        endwin();
        std::cout << "Could not load file" << std::endl;
        return -1;
    }

    V6502::RegisterFile rf = cpu.getRegisterFile();
    rf.programCounter = 0x0400;
    cpu.setRegisterFile(rf);

    // Window dimensions
    int memViewerStartX = 0;
    int memViewerStartY = 0;
    int memViewerWidth = (float) COLS * 0.7;
    int memViewerHeight = (float) LINES * 0.8;

    int cpuStatusStartX = memViewerWidth;
    int cpuStatusStartY = 0;
    int cpuStatusWidth = COLS - memViewerWidth;
    int cpuStatusHeight = memViewerHeight;

    int footerStartX = 0;
    int footerStartY = memViewerHeight;
    int footerWidth = COLS;
    int footerHeight = LINES - memViewerHeight;

    // Other windows
    MemoryViewer memoryViewer(stdscr, memViewerStartX, memViewerStartY, memViewerWidth, memViewerHeight);
    CPUStatus cpuStatus(stdscr, cpuStatusStartX, cpuStatusStartY, cpuStatusWidth, cpuStatusHeight);
    Footer footer(stdscr, footerStartX, footerStartY, footerWidth, footerHeight);

    memoryViewer.update(&cpu, &bus);
    cpuStatus.update(&cpu, &bus);
    footer.update(&cpu, &bus);

    // Refresh windows
    touchwin(stdscr);
    wrefresh(stdscr);

    bool quit = false;
    while(!quit){
        char stopBlock;
        // Get the next key press
        char c = getch();
        switch(c){
            case 'q':
                quit = true;
            break;
            case 'c':
                // stop blocking the getch call
                timeout(0);
                stopBlock = getch();
                while(stopBlock != 'c'){
                    std::this_thread::sleep_for(std::chrono::microseconds(100));
                    cpu.tick();

                    memoryViewer.update(&cpu, &bus);
                    cpuStatus.update(&cpu, &bus);
                    footer.update(&cpu, &bus);

                    // Refresh windows
                    touchwin(stdscr);
                    wrefresh(stdscr);
                    stopBlock = getch();
                }
                timeout(-1);
                break;
            case 's':
                cpu.tick();

                memoryViewer.update(&cpu, &bus);
                cpuStatus.update(&cpu, &bus);
                footer.update(&cpu, &bus);

                // Refresh windows
                touchwin(stdscr);
                wrefresh(stdscr);
            break;
        }
    }

    // Deinitialize ncurses
    endwin();

    return 0;
}