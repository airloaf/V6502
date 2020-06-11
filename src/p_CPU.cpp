#include "p_CPU.h"

using namespace V6502;

CPU::pimpl::pimpl(): mAddressBus(nullptr), mNMI(false), mIRQ(false), mInstruction(nullptr) {
    // Set the CPU in reset mode
    reset();
}

CPU::pimpl::~pimpl(){

}

void CPU::pimpl::tick(){
    // First check any flags and statuses
    if(mReset){
        if(mCurrentResetCycle == 0){

            // Set the stack pointer to 0xFF
            mRegisterFile.stackPointer = 0xFF;

            // Load the program counter from 0xFFFC/FFFD
            uint8_t lowerPC = mAddressBus->read(0xFFFC);
            uint8_t upperPC = mAddressBus->read(0xFFFD);

            // Calculate the program counter and set it
            uint16_t programCounter = lowerPC + (upperPC << 8);
            mRegisterFile.programCounter = programCounter;

            // Set the status register
            // Bit 6 is set to 1 always
            // The interrupt disable is set to true (bit 2)
            mRegisterFile.status = 0x24;

            // Set the two interrupt flags to false
            mNMI = mIRQ = false;
        }

        // Increment the cycle we are on
        mCurrentResetCycle++;

        // Check if we are done with resetting the 6502
        if(mCurrentResetCycle == 6){
            mReset = false;
        }

    }else{
        // Check if we are executing an instruction
        if(mInstruction != nullptr){
            // Tick the instruction
            mInstruction->tick(mAddressBus, mRegisterFile);
        }else{
            // Fetch a new instruction
            uint8_t opcode = mAddressBus->read(mRegisterFile.programCounter);

            // increment the program counter by one
            mRegisterFile.programCounter++;
            
            // Create instruction
            mInstruction = createInstruction(opcode);

            // Perform first tick
            mInstruction->tick(mAddressBus, mRegisterFile);
        }
    }
}

void CPU::pimpl::reset(){
    // Set reset to high
    mReset = true;

    // set reset cycle to 0
    mCurrentResetCycle = 0;
}

void CPU::pimpl::setAddressBus(AddressBus *addressBus){
    mAddressBus = addressBus;
}

bool CPU::pimpl::getNMI(){
    return mNMI;
}

void CPU::pimpl::setNMI(bool set){
    mNMI = set;
}

bool CPU::pimpl::getIRQ(){
    return mIRQ;
}

void CPU::pimpl::setIRQ(bool set){
    mIRQ = set;
}

RegisterFile CPU::pimpl::getRegisterFile(){
    return mRegisterFile;
}

void CPU::pimpl::setRegisterFile(RegisterFile rf){
    mRegisterFile = rf;
}