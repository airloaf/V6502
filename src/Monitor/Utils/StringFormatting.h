#pragma once

#include <string>
#include <ncurses.h>

/**
 * @brief Calculates the x coordinate to render the given text based off the given number of columns
 * 
 * @param text - the text to render
 * @param numCols - the number of columns
 * @return int - X coordinate to move to [0, numCols/2]
 */
int calculateCenterXCoordinate(const std::string &text, int numCols);