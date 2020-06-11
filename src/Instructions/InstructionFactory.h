#pragma once

#include "AddressingModes/AddressingMode.h"
#include "Instruction.h"
#include <stdint.h>

/**
 * @brief Creates an addressing mode based off the type passed in
 * 
 * @param type 
 * @return AddressingMode* 
 */
AddressingMode *createAddressingMode(AddressingModeType type);

/**
 * @brief Create an Instruction based off the given opcode
 * 
 * @param opcode 
 * @return Instruction 
 */
Instruction *createInstruction(uint8_t opcode);