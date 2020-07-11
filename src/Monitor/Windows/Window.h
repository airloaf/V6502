#pragma once

#include <cstddef>
#include <string>

#include <V6502/CPU.h>
#include <V6502/MemoryBus.h>

#include <ncurses.h>

class Window{
    public:

        /**
         * @brief Construct a new Window object
         * 
         * @param stdscr - reference to the stdscr object
         * @param startX - the x coordinate for the top left of the window
         * @param startY - the y coordinate for the top left of the window
         * @param width  - the number of columns this window should be
         * @param height - the number of lines this window should be
         */
        Window(WINDOW *stdscr,
               std::size_t startX,
               std::size_t startY,
               std::size_t width,
               std::size_t height);


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
        virtual void update(V6502::CPU *cpu,
                            V6502::MemoryBus *memoryBus)=0;

    protected:

        void renderText(std::string text,
                        std::size_t xCoordinate,
                        std::size_t yCoordinate);

        void renderTextCenter(std::string text,
                              std::size_t yCoordinate);

        void renderBorder();

        WINDOW *mWindow;

        std::size_t mWidth, mHeight, mStartX, mStartY;
};