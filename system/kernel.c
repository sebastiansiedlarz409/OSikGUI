#include "common.h"
#include "drawing.h"
#include "windows.h"
#include "menu.h"
#include "string.h"
#include "keyboard.h"
#include "interrupt.h"
#include <stdint.h>

void KERN_Load(void* kernelEntryPointAddress, void* stackAddress){
    UNUSED(kernelEntryPointAddress);
    UNUSED(stackAddress);

    DrawString(520, 145, "OSik", 30, RED, BLACK);
    DrawString(700, 520, "Booting!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 0, GREEN, GREY);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(610, 520, "Setup Interrupts!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 20, GREEN, GREY);
    InitInterrupt();
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(635, 520, "Start Timers!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 50, GREEN, GREY);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(620, 520, "Start Usermode!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 100, GREEN, GREY);
    WaitSeconds(1);

    ClearFullScreen();
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress){
    KERN_Load(kernelEntryPointAddress, stackAddress);

    DrawUI();

    //test int 0
    /*WaitSeconds(5);
    int a = 0, b = 0;
    __asm__ volatile("div %2\n"
       : "=d" (a), "=a" (b)
       : "r" (a), "d" (a), "a" (a));*/

    for(;;);
}