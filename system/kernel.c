#include "common.h"
#include "drawing.h"
#include "windows.h"
#include "menu.h"
#include <stdint.h>

void KERN_WaitSeconds(uint64_t seconds){
    uint64_t clock_speed = 400000000;
    seconds*=clock_speed;
    while(seconds--){
        __asm("nop");
    }
}

void KERN_Load(void* kernelEntryPointAddress, void* stackAddress){
    //uint64_t KEPAddr = (uint64_t)kernelEntryPointAddress;
    //uint64_t SAddr = (uint64_t)stackAddress;

    UNUSED(kernelEntryPointAddress);
    UNUSED(stackAddress);

    DrawString(70, 30, "OSik", 10, RED, BLACK);
    DrawProgressBar(130, 140, 190, 150, 0, GREEN, GREY);

    KERN_WaitSeconds(1);

    DrawString(110, 120, "Setup Interrupts!", 1, BLUE, BLACK);
    DrawProgressBar(130, 140, 190, 150, 20, GREEN, GREY);
    KERN_WaitSeconds(1);
    ClearPartScreen(0, 100, 320, 200);

    DrawString(120, 120, "Start Timers!", 1, BLUE, BLACK);
    DrawProgressBar(130, 140, 190, 150, 50, GREEN, GREY);
    KERN_WaitSeconds(1);
    ClearPartScreen(0, 100, 320, 200);

    DrawString(115, 120, "Start Usermode!", 1, BLUE, BLACK);
    DrawProgressBar(130, 140, 190, 150, 100, GREEN, GREY);
    KERN_WaitSeconds(1);
    //ClearPartScreen(0, 100, 320, 200);

    ClearFullScreen();
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress){
    KERN_Load(kernelEntryPointAddress, stackAddress);

    DrawUI();

    /*DrawRectangle(10, 10, 40, 40, GREEN, GREY);

    DrawHorizontalLine(5, 5, 310, DARKRED);
    DrawVerticalLine(5, 5, 190, GREEN);
    DrawVerticalLine(315, 5, 190, GREEN);
    DrawHorizontalLine(5,195, 311, DARKRED);
    
    KERN_WaitSeconds(2);

    DrawLine(5, 5, 50, 50, YELLOW);

    DrawCircle(80, 80, 12, LIGHTCYAN, ORANGE);

    DrawChar(120, 120, 'A', 1, GREEN, BLACK);

    DrawString(140, 30, "Co tam peczek!", 1, RED, BLACK);

    KERN_WaitSeconds(2);

    FillScreen(GREEN);

    KERN_WaitSeconds(2);

    ClearPartScreen(0, 0, 320, 100);*/

    //KERN_WaitSeconds(2);

    //ClearFullScreen();

    for(;;);
}