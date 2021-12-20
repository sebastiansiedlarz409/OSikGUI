#include "common.h"

#include <stdint.h>

static SystemContext context = {
    0, //window
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