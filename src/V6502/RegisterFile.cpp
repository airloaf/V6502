#include <V6502/RegisterFile.h>

// Status register bits
uint8_t STATUS_CARRY        =   2 >> 1;
uint8_t STATUS_ZERO         =   2 << 0;
uint8_t STATUS_IRQ_DISABLE  =   2 << 1;
uint8_t STATUS_DECIMAL_MODE =   2 << 2;
uint8_t STATUS_BRK_COMMAND  =   2 << 3;
uint8_t STATUS_OVERFLOW     =   2 << 5;
uint8_t STATUS_NEGATIVE     =   2 << 6;

using namespace V6502;

bool RegisterFile::getCarry(){
    return (status & STATUS_CARRY) != 0;
}

bool RegisterFile::getZero(){
    return (status & STATUS_ZERO) != 0;
}

bool RegisterFile::getIRQDisable(){
    return (status & STATUS_IRQ_DISABLE) != 0;
}

bool RegisterFile::getDecimalMode(){
    return (status & STATUS_DECIMAL_MODE) != 0;
}

bool RegisterFile::getBRKCommand(){
    return (status & STATUS_BRK_COMMAND) != 0;
}

bool RegisterFile::getOverflow(){
    return (status & STATUS_OVERFLOW) != 0;
}

bool RegisterFile::getNegative(){
    return (status & STATUS_NEGATIVE) != 0;
}

void RegisterFile::setCarry(bool set){
   if(set){
       status |= STATUS_CARRY;
   }else{
       int8_t nextStatus = 0xFF;
       nextStatus -= STATUS_CARRY;
       status &= nextStatus;
   }
}

void RegisterFile::setZero(bool set){
   if(set){
       status |= STATUS_ZERO;
   }else{
       int8_t nextStatus = 0xFF;
       nextStatus -= STATUS_ZERO;
       status &= nextStatus;
   }
}

void RegisterFile::setIRQDisable(bool set){
   if(set){
       status |= STATUS_IRQ_DISABLE;
   }else{
       int8_t nextStatus = 0xFF;
       nextStatus -= STATUS_IRQ_DISABLE;
       status &= nextStatus;
   }
}

void RegisterFile::setDecimalMode(bool set){
   if(set){
       status |= STATUS_DECIMAL_MODE;
   }else{
       int8_t nextStatus = 0xFF;
       nextStatus -= STATUS_DECIMAL_MODE;
       status &= nextStatus;
   }
}

void RegisterFile::setBRKCommand(bool set){
   if(set){
       status |= STATUS_BRK_COMMAND;
   }else{
       int8_t nextStatus = 0xFF;
       nextStatus -= STATUS_BRK_COMMAND;
       status &= nextStatus;
   }
}

void RegisterFile::setOverflow(bool set){
   if(set){
       status |= STATUS_OVERFLOW;
   }else{
       int8_t nextStatus = 0xFF;
       nextStatus -= STATUS_OVERFLOW;
       status &= nextStatus;
   }
}

void RegisterFile::setNegative(bool set){
   if(set){
       status |= STATUS_NEGATIVE;
   }else{
       int8_t nextStatus = 0xFF;
       nextStatus -= STATUS_NEGATIVE;
       status &= nextStatus;
   }
}