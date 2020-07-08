#pragma once

#include <V6502/CPU.h>
#include <V6502/MemoryBus.h>

#include <ncurses.h>

class Window{
    public:

        /**
         * @brief Construct a new Window object
         * 
         * When constructing a new window, we need set its position relative to the stdscr
         * 
         * @param stdscr - reference to the stdscr object
         * @param startX - the x coordinate for the top left of the window
         * @param startY - the y coordinate for the top left of the window
         * @param width  - the number of columns this window should be
         * @param height - the number of lines this window should be
         */
        Window(WINDOW *stdscr, int startX, int startY, int width, int height);


        /**
         * @brief Destroy the Window object
         * 
         * Deconstrutor will remove the subwindow
         */
        virtual ~Window();

        /**
         * @brief Updates the window with the current state of the cpu and memory bus
         * 
         * @param cpu - cpu reference
         * @param memoryBus - memory bus reference
         */
        virtual void update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus);

    protected:
        WINDOW *mWindow; // Subwindow reference

        int mWidth, mHeight, mStartX, mStartY;

};