#include "FileLoaders.h"

#include <fstream>

bool loadBinaryFile(const std::string &file_path, V6502::MemoryBus *bus, uint16_t loadAddress, int size){

    // Open the file in binary mode
    std::ifstream file(file_path.c_str(), std::ios::in | std::ios::binary);

    // Check if the file opened successfully
    if(!file.good()){
        file.close();
        return false;
    }
    uint8_t *data = new uint8_t[size];

    // Read program and character rom
    file.read((char *) data, size);

    // Read all bytes
    for(int address = 0; address < size; address++){
        bus->write(address + loadAddress, data[address]);
    }

    file.close();
    return true;
}