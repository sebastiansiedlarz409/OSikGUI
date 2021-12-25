#include "streams.h"

#include <stdint.h>

Stream STDIN = {
    0
};

void PushInStream(uint8_t value){
    STDIN.buffer[STDIN.size++] = value;
}

uint8_t PopInStream(void){
    uint8_t ret = 0;
    if(STDIN.size>0){
        ret = STDIN.buffer[0];

        for (uint16_t i = 1;i<STDIN.size;i++){
            STDIN.buffer[i-1] = STDIN.buffer[i];
        }
        STDIN.size--;
    }
    return ret;
}