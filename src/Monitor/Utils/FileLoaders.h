#pragma once

#include <V6502/MemoryBus.h>

#include <string>

/**
 * @brief Loads a binary file into the memory bus
 * 
 * @param file_path - path to the file
 * @param bus - memory bus to write into memory
 */
bool loadBinaryFile(const std::string &file_path, V6502::MemoryBus *bus);