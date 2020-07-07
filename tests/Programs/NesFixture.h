#include "../MemoryBus.h"

#include <V6502/CPU.h>
#include <fstream>

struct NESFixture{
    NESFixture(){
        bus = new MemoryBus();
        // Set the address bus to the CPU
        cpu.setMemoryBus(bus);

        // Set the register default values
        V6502::RegisterFile rf = cpu.getRegisterFile();
        rf.accumulator = rf.indexX = rf.indexY = rf.programCounter = 0;
        rf.stackPointer = 0xFF;
        cpu.setRegisterFile(rf);

    }
    ~NESFixture(){}

    void readFile(const std::string &file_path){
        // Open up the file
        std::ifstream file(file_path.c_str(), std::ios::in | std::ios::binary);

        // Check if it could successfully open the file
        if(!file.good()){
            file.close();
            return ;
        }

        // Read the first four bytes (format) , it should say NES followed by 0x1A
        char format[4];
        file.read(format, 4);
        if(format[0] != 'N' || format[1] != 'E' || format[2] != 'S' || format[3] != 0x1A){
            file.close();
            return ;
        }

        // Read the program rom and character rom
        char prgRomSize, chrRomSize;
        file.get(prgRomSize);
        file.get(chrRomSize);

        // Read the next 10 bytes, flags 6 and 7 are contained within the first 2 bytes of this array
        char flags[10];
        file.read(flags, 10);

        uint8_t *prgRomData;
        uint8_t *chrRomData;
        // Allocate size for the program and character rom
        prgRomData = new uint8_t[((int)prgRomSize) * (2 << 13)];
        chrRomData = new uint8_t[((int)chrRomSize) * (2 << 13)];

        // Read program and character rom
        file.read((char *) prgRomData, ((int) prgRomSize) * (2 << 13));
        file.read((char *) chrRomData, ((int) chrRomSize) * (2 << 13));

        if(prgRomSize == 1){
            for(int i = 0; i < (2 << 13); i++){
                bus->write(0x8000 + i, (uint8_t) prgRomData[i]);
                bus->write(0xC000 + i, (uint8_t) prgRomData[i]);
            }
        }

        // Close the file
        file.close();
    }

    MemoryBus *bus;
    V6502::CPU cpu;
};