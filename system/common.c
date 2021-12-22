#include "common.h"

#include <stdint.h>

static SystemContext context = {
    0, //kernel address
    0, //stack address
    0, //heap start address
    0, //heap size
    0, //heap next free address
    1, //window, 0 is BSOD
    2, //max window index
    0  //pointer to main window
};

SystemContext* GetSystemContext(void){
    return &context;
}

int32_t isqrt(int32_t num) {
    int32_t res = 0;
    int32_t bit = 1 << 30; 
    
    while (bit > num)
        bit >>= 2;

    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res = (res >> 1) + bit;
        } else
            res >>= 1;
        bit >>= 2;
    }
    return res;
}

void WaitSeconds(uint64_t seconds){
    uint64_t clock_speed = 400000000;
    seconds*=clock_speed;
    while(seconds--){
        __asm("nop");
    }
}