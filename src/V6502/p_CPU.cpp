#include "p_CPU.h"

using namespace V6502;

CPU::pimpl::pimpl() : mMemoryBus(nullptr), mNMI(false), mIRQ(false), mInstruction(nullptr), mInInterruptHandler(false), mInterruptSequenceCycle(false)
{
    // Set the CPU in reset mode
    reset();
}

CPU::pimpl::~pimpl(){}

void CPU::pimpl::tick()
{
    // First check any flags and statuses
    if (mReset)
    {
        if (mCurrentResetCycle == 0)
        {
            // Set the stack pointer to 0xFF
            mRegisterFile.stackPointer = 0xFF;

            // Load the program counter from 0xFFFC/FFFD
            uint8_t lowerPC = mMemoryBus->read(0xFFFC);
            uint8_t upperPC = mMemoryBus->read(0xFFFD);

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
        if (mCurrentResetCycle == 6)
        {
            mReset = false;
        }

    }// Check if we are currently executing an instruction
    else if (mInstruction != nullptr && !mInstruction->isFinished())
    {
        // Tick the instruction
        mInstruction->tick(mMemoryBus, mRegisterFile);

    }// Check if an interrupt sequence is occuring. Interrupt sequences take 7 cycles including detection of an interrupt
    else if (mInInterruptHandler && mInterruptSequenceCycle < 6)
    {
        // Moving variables declarations out side of swtich statement
        uint16_t interruptVectorAddress = (mIsNMIInterrupt? 0xFFFA : 0xFFFE);
        uint8_t lowPC = mRegisterFile.programCounter & 0x00FF;
        uint8_t highPC = (mRegisterFile.programCounter & 0xFF00) >> 8;

        switch(mInterruptSequenceCycle){
            case 0:
                // Modify the status register
                mRegisterFile.status &= 0xEF;
                mRegisterFile.status |= 0x20;
            break;
            case 1:
                // Push the high bits of PC
                mMemoryBus->write((0x100 + mRegisterFile.stackPointer), highPC);
                mRegisterFile.stackPointer--;
            break;
            case 2:
                // Push the low bits of PC
                mMemoryBus->write((0x100 + mRegisterFile.stackPointer), lowPC);
                mRegisterFile.stackPointer--;
            break;
            case 3:
                // Push the status register
                mMemoryBus->write((0x100 + mRegisterFile.stackPointer), mRegisterFile.status);
                mRegisterFile.stackPointer--;

                if(!mIsNMIInterrupt){
                    // Set IRQ disable flag
                    mRegisterFile.setIRQDisable(true);
                }

            break;
            case 4:
                // Retrieve the low bits of PC from the interrupt vector
                mRegisterFile.programCounter = mMemoryBus->read(interruptVectorAddress);
            break;
            case 5:
                // Retrieve the high bits of PC from the interrupt vector
                mRegisterFile.programCounter |= (mMemoryBus->read(interruptVectorAddress+1) << 8);
            break;
        }
        mInterruptSequenceCycle++;
    }// Check if we are currently not in an interrupt handler, but an interrupt should be initiated. IRQ interrupt should not occur if the IRQ Disable is high
    else if(!mInInterruptHandler && ((mIRQ && !mRegisterFile.getIRQDisable()) || mNMI)){
        mIsNMIInterrupt = mNMI;
        mInterruptSequenceCycle = 0;
        mInInterruptHandler = true;
    }
    else
    {
        // free memory for the previous instruction
        delete mInstruction;

        // Fetch a new instruction
        uint8_t opcode = mMemoryBus->read(mRegisterFile.programCounter);

        // increment the program counter by one
        mRegisterFile.programCounter++;

        // Create instruction
        mInstruction = createInstruction(opcode);

        // TODO: Check for BRK instruction
        if(mInstruction->getType() == InstructionType::BRK){
            mInInterruptHandler = true;
            mInterruptSequenceCycle = 6;
        }else if(mInstruction->getType() == InstructionType::RTI){
            // no longer in interrupt handler
            mInInterruptHandler = false;
            // Reset the interrupt sequence cycle to 0
            mInterruptSequenceCycle = 0;
        }

        // Perform first tick
        mInstruction->tick(mMemoryBus, mRegisterFile);
    }
}

void CPU::pimpl::reset()
{
    // Set reset to high
    mReset = true;

    // set reset cycle to 0
    mCurrentResetCycle = 0;
}

void CPU::pimpl::setMemoryBus(MemoryBus *memoryBus)
{
    mMemoryBus = memoryBus;
}

bool CPU::pimpl::getNMI()
{
    return mNMI;
}

void CPU::pimpl::setNMI(bool set)
{
    mNMI = set;
}

bool CPU::pimpl::getIRQ()
{
    return mIRQ;
}

void CPU::pimpl::setIRQ(bool set)
{
    mIRQ = set;
}

RegisterFile CPU::pimpl::getRegisterFile()
{
    return mRegisterFile;
}

void CPU::pimpl::setRegisterFile(RegisterFile rf)
{
    mRegisterFile = rf;
}