#include "Footer.h"

#include "../Utils/StringFormatting.h"

Footer::Footer(WINDOW *stdscr, int startX, int startY, int width, int height)
: Window(stdscr, startX, startY, width, height){
    mInputAddress[4] = 0;
}

Footer::~Footer(){

}

void Footer::update(V6502::CPU *cpu, V6502::MemoryBus *memoryBus){

    renderBorder();

    std::string title = "Instructions";
    renderTextCenter(title, 1);

    renderText("- s: Step", 1, 2);
    renderText("- c: Toggle Continuous Execution", 1, 3);
    renderText("- q: Quit", 1, 4);
    renderText("- j: Scroll Zero Page Down", 40, 2);
    renderText("- k: Scroll Zero Page Up", 40, 3);
    renderText("- /: Go to memory address", 40, 4);
    wprintw(mWindow, " $0x%s", mInputAddress);

}

void Footer::setInputAddress(int index, char key){
    mInputAddress[index] = key;
}

void Footer::clearInputAddress(){
    for(int i = 0; i < 4; i++){
        mInputAddress[i] = ' ';
    }
}

uint16_t Footer::calculateAddress(){
    uint16_t ret = 0;
    for(int i = 0; i < 3; i++){
        char num = mInputAddress[i];
        if(num >= '0' && num <= '9'){
            ret += (int) (num - '0');
        }else{
            ret += (10 + (int) (num - 'a'));
        }
        ret <<= 4;
    }
    char num = mInputAddress[3];
    if(num >= '0' && num <= '9'){
        ret += (int) (num - '0');
    }else{
        ret += (10  + (int) (num - 'a'));
    }
    return ret;
}