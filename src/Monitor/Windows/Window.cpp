#include "Window.h"

#include <iostream>

Window::Window(WINDOW *stdscr, int startX, int startY, int width, int height)
    : mWidth(width), mHeight(height), mStartX(startX), mStartY(startY){
    mWindow = subwin(stdscr, height, width, startY, startX);
}

Window::~Window(){
    delwin(mWindow);
}
void Window::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){
    box(mWindow, '|', '-');
}