#include "Window.h"

#include "../Utils/StringFormatting.h"

Window::Window(WINDOW *stdscr,
               std::size_t startX,
               std::size_t startY,
               std::size_t width,
               std::size_t height)
    : mWidth(width), mHeight(height), mStartX(startX), mStartY(startY){
    mWindow = subwin(stdscr, height, width, startY, startX);
}

Window::~Window(){
    delwin(mWindow);
}

void Window::renderText(std::string text,
                        std::size_t xCoordinate,
                        std::size_t yCoordinate){
    wmove(mWindow, yCoordinate, xCoordinate);
    wprintw(mWindow, "%s", text.c_str());
}

void Window::renderTextCenter(std::string text,
                              std::size_t yCoordinate){
    std::size_t centerX = calculateCenterXCoordinate(text, mWidth);
    renderText(text, centerX, yCoordinate);
}

void Window::renderBorder(){
    box(mWindow, '|', '-');
}