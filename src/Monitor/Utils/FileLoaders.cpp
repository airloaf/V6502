#include "FileLoaders.h"

#include <fstream>

bool loadBinaryFile(const std::string &file_path, V6502::MemoryBus *bus){

    // Open the file in binary mode
    std::ifstream file(file_path.c_str(), std::ios::in | std::ios::binary);

    // Check if the file opened successfully
    if(!file.good()){
        file.close();
        return false;
    }
    uint8_t data[0x1000];

    // Read program and character rom
    file.read((char *) &data, 0x1000);

    // Read all bytes
    for(int address = 0; address < 0x10000; address++){
        bus->write(address, data[address]);
    }

    file.close();
    return true;
}