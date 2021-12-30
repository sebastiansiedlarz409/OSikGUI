#include "include/common.h"
#include "include/streams.h"

#include <stdint.h>

static SystemContext context = {
    0, //kernel address
    0, //stack address
    0, //apps address
    0, //heap start address
    0, //heap size
    0, //heap next free address
    1, //window, 0 is BSOD
    2, //max window index
    0, //pointer to main window
    0, //pointer to last created window
    0, //index of current window
    PushInStream, //pointer to push stdin
    PopInStream, //pointer to pop stdin
    GetInStreamSize, //pointer to func returning size of stdin
};

SystemContext* GetSystemContext(void){
    return &context;
}

void WaitSeconds(uint64_t seconds){
    uint64_t clock_speed = 400000000;
    seconds*=clock_speed;
    while(seconds--){
        __asm("nop");
    }
}

void Swap(uint64_t* a, uint64_t* b){
    *a+=*b;
    *b=*a-*b;
    *a-=*b;
}