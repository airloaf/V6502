#pragma once

#include "AddressingMode.h"
#include "Instruction.h"
#include <stdint.h>

/**
 * @brief Create an Instruction based off the given opcode
 * 
 * @param opcode 
 * @return Instruction 
 */
Instruction *createInstruction(uint16_t opcode);