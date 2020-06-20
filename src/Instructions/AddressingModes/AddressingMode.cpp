#include "AddressingMode.h"

namespace V6502{ namespace AddressingModes{

// Default for all addressing modes
bool AddressingMode::hasCrossedPageBoundary(){
    return false;
}
}}