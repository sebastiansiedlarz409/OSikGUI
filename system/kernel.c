#include "common.h"
#include "drawing.h"
#include "windows.h"
#include "menu.h"
#include "interrupt.h"
#include <stdint.h>

void KERN_Load(void* kernelEntryPointAddress, void* stackAddress){
    UNUSED(kernelEntryPointAddress);
    UNUSED(stackAddress);

    DrawString(520, 145, 30, RED, BLACK, "OSik");
    DrawString(700, 520, 5, BLUE, BLACK, "Booting!");
    DrawProgressBar(610, 620, 1020, 670, 0, GREEN, GREY);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(610, 520, 5, BLUE, BLACK, "Setup Interrupts!");
    DrawProgressBar(610, 620, 1020, 670, 20, GREEN, GREY);
    InitInterrupt();
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(635, 520, 5, BLUE, BLACK, "Start Timers!");
    DrawProgressBar(610, 620, 1020, 670, 50, GREEN, GREY);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(620, 520, 5, BLUE, BLACK, "Start Usermode!");
    DrawProgressBar(610, 620, 1020, 670, 100, GREEN, GREY);
    WaitSeconds(1);
    //ClearPartScreen(0, 520, 1600, 1200);

    ClearFullScreen();
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress){
    KERN_Load(kernelEntryPointAddress, stackAddress);

    DrawUI();

    //DrawPixel(0,0,RED);
    //DrawPixel(1,0,BLUE);

    //DrawRectangle(10, 10, 300, 600, GREEN, GREY);

    /*DrawHorizontalLine(5, 5, 310, DARKRED);
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

    //test int 0
    WaitSeconds(10);
    int a = 0, b = 0;
    __asm__ volatile("div %2\n"
       : "=d" (a), "=a" (b)
       : "r" (a), "d" (a), "a" (a));

    for(;;);
}