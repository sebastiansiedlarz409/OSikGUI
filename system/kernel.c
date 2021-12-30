#include "include/api.h"
#include "include/common.h"
#include "include/drawing.h"
#include "include/windows.h"
#include "include/menu.h"
#include "include/heap.h"
#include "include/loader.h"
#include "include/streams.h"
#include "include/string.h"
#include "include/keyboard.h"
#include "include/interrupt.h"

#include <stdint.h>

void KERN_Load(void* kernelEntryPointAddress, void* stackAddress, void* appsTableAddress){
    GetSystemContext()->kernelAddress=(uint64_t)kernelEntryPointAddress;
    GetSystemContext()->stackAddress=(uint64_t)stackAddress;
    GetSystemContext()->appsTableAddress=(uint64_t)appsTableAddress;

    DrawWLine(100, 100, 200, 200, 5, BLUE); // \d

    DrawWLine(600,400,400,600, 5,RED); // /d

    DrawWLine(900, 700, 1200, 300, 5, GREEN); // /u

    DrawWLine(1300, 800, 1000, 600, 5, PINK); // \u

    DrawWLine(50, 550, 50, 600, 5, MAGENTA); //|
    DrawWLine(80, 580, 80, 450, 5, LIGHTCYAN); //|
    
    DrawWLine(300, 80, 800, 80, 5, LIGHTYELLOW); //-
    DrawWLine(800, 120, 600, 120, 5, PERSIAPINK); //-

    //DrawLine(100,100,100,300,GREEN);

    RefreshScreen();
    for(;;);

    DrawString(520, 145, "OSik", 30, RED, BLACK);
    DrawString(700, 520, "Booting!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 0, GREEN, AMBER);
    RefreshScreen();
    InitHeap(0x600000, 0x200000);
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(610, 520, "Setup Interrupts!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 20, GREEN, AMBER);
    RefreshScreen();
    InitInterrupt();
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(635, 520, "Start Timers!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 50, GREEN, AMBER);
    RefreshScreen();
    WaitSeconds(1);
    ClearPartScreen(0, 520, 1600, 1200);

    DrawString(620, 520, "Start Usermode!", 5, BLUE, BLACK);
    DrawProgressBar(610, 620, 1020, 670, 100, GREEN, AMBER);
    InitAPI();
    RefreshScreen();
    WaitSeconds(1);
}

void KERN_Start(void* kernelEntryPointAddress, void* stackAddress, void* appsTableAddress){
    KERN_Load(kernelEntryPointAddress, stackAddress, appsTableAddress);

    DrawUI();

    //test int 0
    /*WaitSeconds(5);
    int a = 0, b = 0;
    __asm__ volatile("div %2\n"
       : "=d" (a), "=a" (b)
       : "r" (a), "d" (a), "a" (a));*/

    for(;;);
}