#include "StringFormatting.h"

int calculateCenterXCoordinate(const std::string &text, int numCols){
    return (numCols / 2) - (text.length()/2);
}