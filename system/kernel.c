#include "common.h"
#include "drawing.h"
#include <stdint.h>

void KERN_WaitSeconds(uint64_t seconds){
    uint64_t clock_speed = 400000000;
    seconds*=clock_speed;
    while(seconds--){
        __asm("nop");
    }
}

void KERN_Welcome(void* kernelEntryPointAddress, void* stackAddress){
    uint64_t KEPAddr = (uint64_t)kernelEntryPointAddress;
    uint64_t SAddr = (uint64_t)stackAddress;
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress){
    DrawRectangle(10, 10, 40, 40, GREEN, GREY);

    DrawHorizontalLine(5, 5, 310, DARKRED);
    DrawVerticalLine(5, 5, 190, GREEN);
    DrawVerticalLine(315, 5, 190, GREEN);
    DrawHorizontalLine(5,195, 311, DARKRED);
    
    KERN_WaitSeconds(2);

    DrawLine(5, 5, 50, 50, YELLOW);

    DrawCircle(80, 80, 12, LIGHTCYAN, ORANGE);

    DrawChar(120, 120, 'A', 1, GREEN, BLACK);

    DrawString(140, 30, "Co tam peczek!", 1, RED, BLACK);

    for(;;);
}